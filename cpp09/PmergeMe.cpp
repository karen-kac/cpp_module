#include "PmergeMe.hpp"
#include <cstdlib>
#include <climits>
#include <cstddef>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <deque>
#include <cmath>

// 本ファイルの目的:
//  - 引数から正の整数列を読み取り、vector / deque の両方で
//    Ford–Johnson（merge-insertion）法に基づくソートを実行する。
//  - 計測（クロック）と比較回数の概算カウントを行い出力する。
//
// Ford–Johnson（merge-insertion）法の超概要:
//  1) 要素をペアに分割し、各ペアで大小比較して [larger, smaller] を得る。
//  2) 全ての larger だけを取り出して再帰的に整列（main chain を作る）。
//  3) smaller および奇数番目の余り（straggler）を、ヤコブスタル順に
//     main chain に二分探索で挿入する（探索上限を Jacobsthal により制限）。
//  この手順により、比較回数の理論的下限に近い挙動を目指す。

// Orthodox Canonical Form
PmergeMe::PmergeMe() : _count(0) {}

PmergeMe::PmergeMe(int argc, char **argv) : _count(0) {
	(void)argc;
	if (!load_container(argv))
		throw std::runtime_error("Fail to load content");
}

PmergeMe::PmergeMe(const PmergeMe& other)
	: vector_container(other.vector_container)
	, deque_container(other.deque_container)
	, _start(other._start)
	, _end(other._end)
	, _count(other._count)
{}

PmergeMe& PmergeMe::operator=(const PmergeMe &other) {
	if (this == &other) return *this;
	vector_container = other.vector_container;
	deque_container = other.deque_container;
	_start = other._start;
	_end = other._end;
	_count = other._count;
	return *this;
}

PmergeMe::~PmergeMe() {}

// Parse
// C 由来の strtol を用いて 10 進の正の整数を解析する。
// - 先頭から末尾までが数字であること
// - 1 以上 INT_MAX 以下であること
// を満たす場合のみ true を返す。
bool PmergeMe::parseInt(char* s, int& out) const {
	char *endp;
	long val = std::strtol(s, &endp, 10);
	if (*endp != '\0' || val <= 0 || val > INT_MAX)
		return false;
	out = static_cast<int>(val);
	return true;
}

// Load
// argv[1:] を順に整数へ変換し、vector と deque の両方に同一の内容を格納する。
bool PmergeMe::load_container(char **argv) {
	for (int i = 1; argv[i]; ++i) {
		int x;
		if (!parseInt(argv[i], x))
			return false;
		vector_container.push_back(x);
		deque_container.push_back(x);
	}
	return true;
}

// Print
void PmergeMe::print_elapsed_time() const {
	double elapsed_time = static_cast<double>(_end - _start) / CLOCKS_PER_SEC * 1e6;
	std::cout	<< "Time to process a range of " << vector_container.size()
				<< " elements : " 
				<< std::fixed << std::setprecision(6) << elapsed_time
				<< " us" << std::endl;
}

void PmergeMe::print_elements() const {
	size_t count = 0;
	size_t max = 21;
	for (std::vector<int>::const_iterator it = vector_container.begin(); it != vector_container.end() && count < max; ++it, ++count) {
		std::cout << (count ? " " : "") << *it;
	}
	if (vector_container.size() > max) std::cout << " [...]";
	std::cout << std::endl;
}

void PmergeMe::print_deque_elements() const {
	size_t count = 0;
	size_t max = 21;
	for (std::deque<int>::const_iterator it = deque_container.begin(); it != deque_container.end() && count < max; ++it, ++count) {
		std::cout << (count ? " " : "") << *it;
	}
	if (deque_container.size() > max) std::cout << " [...]";
	std::cout << std::endl;
}

// IndexedPair
// 各ペアで「大きい方（larger）」「小さい方（smaller）」を保持する構造体。
// original_index はペアの元の順序を識別するための情報（挿入順制御に利用）。
struct IndexedPair {
	int larger;
	int smaller;
	size_t original_index;
	IndexedPair(int l, int s, size_t idx) : larger(l), smaller(s), original_index(idx) {}
};

// LargerWithIndex
// larger の値と、それがどのペア由来かを保持する構造体（再帰ソート用）
struct LargerWithIndex {
	int value;
	size_t original_index;
	LargerWithIndex(int v, size_t idx) : value(v), original_index(idx) {}
};

// ヤコブスタル順のブロック端点列 J を生成する。
// J = [1, 3, 5, 11, 21, ...] を m まで伸長し、末端が m で終わるよう調整する。
static std::vector<size_t> make_jacobsthal_breaks(size_t m) {
	std::vector<size_t> J;
	if (m == 0) return J;
	J.push_back(1);
	if (m == 1) return J; // J = [1]

	size_t j_prev = 1, j_curr = 3;
	while (j_curr < m) {
		J.push_back(j_curr);
		size_t j_next = j_curr + 2 * j_prev;
		j_prev = j_curr;
		j_curr = j_next;
	}
	if (J.back() != m) J.push_back(m); // 終端を m に揃える
	return J;
}

// ヤコブスタル順に基づく 1 始まりの挿入順序（サイズ m）を生成する。
// 具体的には、J により区切られる各ブロック (prev, x] を降順で列挙して結合する。
static std::vector<size_t> make_jacobsthal_order(size_t m) {
	std::vector<size_t> order;
	if (m == 0) return order;
	if (m == 1) { order.push_back(1); return order; }

	const std::vector<size_t> J = make_jacobsthal_breaks(m);
	order.reserve(m);

	size_t prev = 0;
	for (size_t bi = 0; bi < J.size(); ++bi) {
		const size_t x = J[bi];                 // このブロックの終端(含む)
		// 全ブロック: (prev, x] を降順で
		for (size_t pos = x; pos > prev; --pos) order.push_back(pos);
		prev = x;
	}
	return order; // サイズ m
}

// === LargerWithIndex の再帰ソート（vector 版） ===
static void ford_johnson_larger_vector(std::vector<LargerWithIndex>& larger_list, size_t& comp_count) {
	const size_t n = larger_list.size();
	if (n <= 1) return;

	// 1) ペア化
	std::vector<IndexedPair> pairs;
	pairs.reserve(n / 2);
	bool has_straggler = (n % 2) != 0;
	LargerWithIndex straggler(0, 0);

	for (size_t i = 0; i + 1 < n; i += 2) {
		comp_count++;
		if (larger_list[i].value > larger_list[i + 1].value) {
			pairs.push_back(IndexedPair(i, i + 1, i / 2));
		} else {
			pairs.push_back(IndexedPair(i + 1, i, i / 2));
		}
	}
	if (has_straggler) straggler = larger_list[n - 1];
	if (pairs.empty()) return;

	// 2) larger のインデックスを抽出して再帰
	std::vector<LargerWithIndex> sub_larger;
	sub_larger.reserve(pairs.size());
	for (size_t i = 0; i < pairs.size(); ++i) {
		sub_larger.push_back(larger_list[pairs[i].larger]);
	}

	ford_johnson_larger_vector(sub_larger, comp_count);

	// 3) ソート済み larger に基づいてペアを復元（original_index で対応）
	std::vector<IndexedPair> sorted_pairs;
	sorted_pairs.reserve(pairs.size());
	for (size_t i = 0; i < sub_larger.size(); ++i) {
		size_t want_idx = sub_larger[i].original_index;
		for (size_t j = 0; j < pairs.size(); ++j) {
			if (pairs[j].original_index != SIZE_MAX && larger_list[pairs[j].larger].original_index == want_idx) {
				sorted_pairs.push_back(pairs[j]);
				pairs[j].original_index = SIZE_MAX; // 使用済みマーク
				break;
			}
		}
	}

	// 4) result 構築
	std::vector<LargerWithIndex> result;
	result.reserve(n);
	for (size_t i = 0; i < sorted_pairs.size(); ++i) {
		result.push_back(larger_list[sorted_pairs[i].larger]);
	}

	// pending = smaller + straggler
	std::vector<LargerWithIndex> pending;
	pending.reserve(sorted_pairs.size() + (has_straggler ? 1 : 0));
	for (size_t i = 0; i < sorted_pairs.size(); ++i) {
		pending.push_back(larger_list[sorted_pairs[i].smaller]);
	}
	if (has_straggler) pending.push_back(straggler);
	if (pending.empty()) { larger_list = result; return; }

	// 5) Jacobsthal 順に挿入
	const std::vector<size_t> J = make_jacobsthal_breaks(pending.size());
	const std::vector<size_t> order = make_jacobsthal_order(pending.size());

	for (size_t k = 0; k < order.size(); ++k) {
		size_t one_based = order[k];
		size_t idx = one_based - 1;
		LargerWithIndex to_insert = pending[idx];

		// partner の現在位置を探す
		size_t partner_pos = result.size();
		if (idx < sorted_pairs.size()) {
			size_t partner_orig_idx = larger_list[sorted_pairs[idx].larger].original_index;
			for (size_t i = 0; i < result.size(); ++i) {
				if (result[i].original_index == partner_orig_idx) {
					partner_pos = i;
					break;
				}
			}
		}

		// Jacobsthal 上限
		size_t jacobsthal_limit = 0;
		for (size_t i = 0; i < J.size(); ++i) {
			if (one_based <= J[i]) {
				jacobsthal_limit = J[i];
				break;
			}
		}

		size_t main_chain_initial = sorted_pairs.size();
		size_t search_limit = main_chain_initial + jacobsthal_limit;
		size_t right = std::min(partner_pos, search_limit);

		// 二分探索
		size_t left = 0;
		while (left < right) {
			size_t mid = left + (right - left) / 2;
			comp_count++;
			if (result[mid].value < to_insert.value) {
				left = mid + 1;
			} else {
				right = mid;
			}
		}
		result.insert(result.begin() + left, to_insert);
	}

	larger_list = result;
}

// === Ford–Johnson（merge-insertion）法の vector 実装（改良版） ===
static void ford_johnson_vector_impl(std::vector<int>& v, size_t& comp_count) {
	const size_t n = v.size();
	if (n <= 1) return;

	// 1) ペア化
	std::vector<IndexedPair> pairs;
	pairs.reserve(n / 2);
	bool has_straggler = (n % 2) != 0;
	int straggler = 0;

	for (size_t i = 0; i + 1 < n; i += 2) {
		comp_count++;
		if (v[i] > v[i + 1]) {
			pairs.push_back(IndexedPair(v[i], v[i + 1], i / 2));
		} else {
			pairs.push_back(IndexedPair(v[i + 1], v[i], i / 2));
		}
	}
	if (has_straggler) straggler = v[n - 1];
	if (pairs.empty()) return;

	// 2) larger を original_index と共に抽出して再帰ソート
	std::vector<LargerWithIndex> larger_list;
	larger_list.reserve(pairs.size());
	for (size_t i = 0; i < pairs.size(); ++i) {
		larger_list.push_back(LargerWithIndex(pairs[i].larger, pairs[i].original_index));
	}

	ford_johnson_larger_vector(larger_list, comp_count);

	// 3) ソート済み larger に基づいてペアを復元（original_index で対応）
	std::vector<IndexedPair> sorted_pairs;
	sorted_pairs.reserve(pairs.size());
	for (size_t i = 0; i < larger_list.size(); ++i) {
		size_t want_idx = larger_list[i].original_index;
		for (size_t j = 0; j < pairs.size(); ++j) {
			if (pairs[j].original_index == want_idx) {
				sorted_pairs.push_back(pairs[j]);
				pairs[j].original_index = SIZE_MAX; // 使用済みマーク
				break;
			}
		}
	}

	// 4) 初期 result = [全 larger]（original_indexと共に保持）
	std::vector<LargerWithIndex> result;
	result.reserve(v.size());
	for (size_t i = 0; i < sorted_pairs.size(); ++i) {
		result.push_back(LargerWithIndex(sorted_pairs[i].larger, sorted_pairs[i].original_index));
	}

	// pending = 全ての smaller + straggler（original_indexと共に保持）
	std::vector<LargerWithIndex> pending;
	pending.reserve(sorted_pairs.size() + (has_straggler ? 1 : 0));
	for (size_t i = 0; i < sorted_pairs.size(); ++i) {
		pending.push_back(LargerWithIndex(sorted_pairs[i].smaller, sorted_pairs[i].original_index));
	}
	if (has_straggler) pending.push_back(LargerWithIndex(straggler, SIZE_MAX));
	if (pending.empty()) {
		v.clear();
		for (size_t i = 0; i < result.size(); ++i) v.push_back(result[i].value);
		return;
	}

	// 5) Jacobsthal 順に挿入
	const std::vector<size_t> J = make_jacobsthal_breaks(pending.size());
	const std::vector<size_t> order = make_jacobsthal_order(pending.size());

	for (size_t k = 0; k < order.size(); ++k) {
		size_t one_based = order[k];
		size_t idx = one_based - 1;
		LargerWithIndex to_insert = pending[idx];

		// partner の現在位置を探す（original_indexで識別）
		size_t partner_pos = result.size();
		if (idx < sorted_pairs.size()) {
			size_t partner_orig_idx = sorted_pairs[idx].original_index;
			for (size_t i = 0; i < result.size(); ++i) {
				if (result[i].original_index == partner_orig_idx) {
					partner_pos = i;
					break;
				}
			}
		}

		// Jacobsthal 上限
		size_t jacobsthal_limit = 0;
		for (size_t i = 0; i < J.size(); ++i) {
			if (one_based <= J[i]) {
				jacobsthal_limit = J[i];
				break;
			}
		}

		size_t main_chain_initial = sorted_pairs.size();
		size_t search_limit = main_chain_initial + jacobsthal_limit;
		size_t right = std::min(partner_pos, search_limit);

		// 二分探索
		size_t left = 0;
		while (left < right) {
			size_t mid = left + (right - left) / 2;
			comp_count++;
			if (result[mid].value < to_insert.value) {
				left = mid + 1;
			} else {
				right = mid;
			}
		}
		result.insert(result.begin() + left, to_insert);
	}

	// 最終的に値だけを抽出してvに代入
	v.clear();
	v.reserve(result.size());
	for (size_t i = 0; i < result.size(); ++i) {
		v.push_back(result[i].value);
	}
}

// === Ford–Johnson（merge-insertion）法の deque 実装（改良版） ===
static void ford_johnson_deque_impl(std::deque<int>& d, size_t& comp_count) {
	const size_t n = d.size();
	if (n <= 1) return;

	// 1) ペア化
	std::deque<IndexedPair> pairs;
	bool has_straggler = (n % 2) != 0;
	int straggler = 0;

	for (size_t i = 0; i + 1 < n; i += 2) {
		comp_count++;
		if (d[i] > d[i + 1]) {
			pairs.push_back(IndexedPair(d[i], d[i + 1], i / 2));
		} else {
			pairs.push_back(IndexedPair(d[i + 1], d[i], i / 2));
		}
	}
	if (has_straggler) straggler = d[n - 1];
	if (pairs.empty()) return;

	// 2) larger を original_index と共に抽出して再帰ソート（vector 版を流用）
	std::vector<LargerWithIndex> larger_list;
	larger_list.reserve(pairs.size());
	for (size_t i = 0; i < pairs.size(); ++i) {
		larger_list.push_back(LargerWithIndex(pairs[i].larger, pairs[i].original_index));
	}

	ford_johnson_larger_vector(larger_list, comp_count);

	// 3) ソート済み larger に基づいてペアを復元（original_index で対応）
	std::deque<IndexedPair> sorted_pairs;
	for (size_t i = 0; i < larger_list.size(); ++i) {
		size_t want_idx = larger_list[i].original_index;
		for (size_t j = 0; j < pairs.size(); ++j) {
			if (pairs[j].original_index == want_idx) {
				sorted_pairs.push_back(pairs[j]);
				pairs[j].original_index = SIZE_MAX; // 使用済みマーク
				break;
			}
		}
	}

	// 4) 初期 result = [全 larger]（original_indexと共に保持）
	std::vector<LargerWithIndex> result;
	result.reserve(d.size());
	for (size_t i = 0; i < sorted_pairs.size(); ++i) {
		result.push_back(LargerWithIndex(sorted_pairs[i].larger, sorted_pairs[i].original_index));
	}

	// pending = 全ての smaller + straggler（original_indexと共に保持）
	std::vector<LargerWithIndex> pending;
	pending.reserve(sorted_pairs.size() + (has_straggler ? 1 : 0));
	for (size_t i = 0; i < sorted_pairs.size(); ++i) {
		pending.push_back(LargerWithIndex(sorted_pairs[i].smaller, sorted_pairs[i].original_index));
	}
	if (has_straggler) pending.push_back(LargerWithIndex(straggler, SIZE_MAX));
	if (pending.empty()) {
		d.clear();
		for (size_t i = 0; i < result.size(); ++i) d.push_back(result[i].value);
		return;
	}

	// 5) Jacobsthal 順に挿入
	const std::vector<size_t> J = make_jacobsthal_breaks(pending.size());
	const std::vector<size_t> order = make_jacobsthal_order(pending.size());

	for (size_t k = 0; k < order.size(); ++k) {
		size_t one_based = order[k];
		size_t idx = one_based - 1;
		LargerWithIndex to_insert = pending[idx];

		// partner の現在位置を探す（original_indexで識別）
		size_t partner_pos = result.size();
		if (idx < sorted_pairs.size()) {
			size_t partner_orig_idx = sorted_pairs[idx].original_index;
			for (size_t i = 0; i < result.size(); ++i) {
				if (result[i].original_index == partner_orig_idx) {
					partner_pos = i;
					break;
				}
			}
		}

		// Jacobsthal 上限
		size_t jacobsthal_limit = 0;
		for (size_t i = 0; i < J.size(); ++i) {
			if (one_based <= J[i]) {
				jacobsthal_limit = J[i];
				break;
			}
		}

		size_t main_chain_initial = sorted_pairs.size();
		size_t search_limit = main_chain_initial + jacobsthal_limit;
		size_t right = std::min(partner_pos, search_limit);

		// 二分探索
		size_t left = 0;
		while (left < right) {
			size_t mid = left + (right - left) / 2;
			comp_count++;
			if (result[mid].value < to_insert.value) {
				left = mid + 1;
			} else {
				right = mid;
			}
		}
		result.insert(result.begin() + left, to_insert);
	}

	// 最終的に値だけを抽出してdに代入
	d.clear();
	for (size_t i = 0; i < result.size(); ++i) {
		d.push_back(result[i].value);
	}
}


void PmergeMe::sort_ford_johnson_vector() {
	_start = std::clock();
	_count = 0;
	if (vector_container.size() <= 1) {
		_end = std::clock();
		return;
	}
	ford_johnson_vector_impl(vector_container, _count);
	_end = std::clock();
}

void PmergeMe::sort_ford_johnson_deque() {
	_start = std::clock();
	_count = 0;
	if (deque_container.size() <= 1) {
		_end = std::clock();
		return;
	}
	ford_johnson_deque_impl(deque_container, _count);
	_end = std::clock();
}

void PmergeMe::run() {
	std::cout << "Before: ";
	print_elements();
	// ベクター版のソートと計測

	std::cout << "\n=== Vector ===" << std::endl;
	sort_ford_johnson_vector();
	std::cout << "After: ";
	print_elements();
	print_elapsed_time();
	std::cout << "比較回数 : " << _count << std::endl;
	// デック版のソートと計測
	std::cout << "\n=== Deque ===" << std::endl;
	sort_ford_johnson_deque();
	std::cout << "After: ";
	print_deque_elements();
	print_elapsed_time();
	std::cout << "比較回数 : " << _count << std::endl;
}
