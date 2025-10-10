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

// Debug removed

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

// === partner の現在位置を探す（比較カウントには含めない） ===
// Jacobsthal に基づき、同じペアの larger が到達できる位置の右側には
// smaller を挿入しないという制約があるため、partner の位置を知る必要がある。
template <typename Seq>
static size_t locate_partner_pos(const Seq& result, int partner_value) {
	for (size_t i = 0; i < result.size(); ++i) {
		if (result[i] == partner_value) return i;
	}
	return result.size(); // 見つからなければ全域にする保険
}

// === 以降：実装本体（vector / deque） ===

// 重複定義は上部のものを使用

// Ford–Johnson（merge-insertion）法の vector 実装。
// comp_count は大小比較の回数を概算カウントするためにインクリメントする。
static void ford_johnson_vector_impl(std::vector<int>& v, size_t& comp_count) {
	const size_t n = v.size();
	if (n <= 1) return;

	// 1) ペア化
	//    [a0, a1], [a2, a3], ... と 2 つずつ取り、1 回の比較で larger/smaller を確定。
	//    奇数個のときは最後の 1 要素を straggler（余り）として後段で挿入する。
	std::vector<IndexedPair> pairs;
	pairs.reserve(n / 2);
	bool has_straggler = (n % 2) != 0;
	int straggler = 0;

	for (size_t i = 0; i + 1 < n; i += 2) {
		comp_count++;
		if (v[i] > v[i + 1]) pairs.push_back(IndexedPair(v[i], v[i + 1], i / 2));
		else                 pairs.push_back(IndexedPair(v[i + 1], v[i], i / 2));
	}
	if (has_straggler) straggler = v[n - 1];
	if (pairs.empty()) return;

	// 2) larger 抽出 → 再帰整列
	//    全ペアの larger のみを取り出して再帰的に整列し、main chain を作る。
	std::vector<int> larger_values;
	larger_values.reserve(pairs.size());
	for (size_t i = 0; i < pairs.size(); ++i) larger_values.push_back(pairs[i].larger);

	ford_johnson_vector_impl(larger_values, comp_count);

	// 整列順に元ペアへ復元
	//  - larger_values は昇順（もしくは非降順）に並んでいる。
	//  - 値が重複する可能性があるため、未使用の一致を順に消費して対応付ける。
	std::vector<IndexedPair> sorted_pairs;
	sorted_pairs.reserve(pairs.size());
	for (size_t i = 0; i < larger_values.size(); ++i) {
		int want = larger_values[i];
		for (size_t j = 0; j < pairs.size(); ++j) {
			if (pairs[j].larger == want) {
				sorted_pairs.push_back(pairs[j]);
				pairs[j].larger = INT_MIN; // 使用済みマーク
				break;
			}
		}
	}

	// 初期 result = [全 larger]
	std::vector<int> result;
	result.reserve(v.size());
	for (size_t i = 0; i < sorted_pairs.size(); ++i) result.push_back(sorted_pairs[i].larger);

	// pending = 全ての smaller + straggler
	// ここから Jacobsthal の順序と上限制御を用いて、二分探索で挿入していく。
	std::vector<int> pending;
	pending.reserve(sorted_pairs.size() + (has_straggler ? 1 : 0));
	for (size_t i = 0; i < sorted_pairs.size(); ++i) pending.push_back(sorted_pairs[i].smaller);
	if (has_straggler) pending.push_back(straggler);
	if (pending.empty()) { v = result; return; }

	// Jacobsthal 順と J ブレーク
	//  - order: smaller を挿入する 1 始まりの順序
	//  - J: 探索許容範囲を段階的に広げるためのブロック端点
	const std::vector<size_t> J = make_jacobsthal_breaks(pending.size());
	const std::vector<size_t> order = make_jacobsthal_order(pending.size());

	// Jacobsthal に従って pending の要素を main chain（result）へ挿入
	// ポイント:
	//  - 同ペアの larger の「現在位置」より右には挿入しない（安定な上限制御）。
	//  - また、main chain の初期長 + J ブロックの大きさ までに探索を制限する。
	//  - 実際の位置決定は二分探索で行い、comp_count を比較ごとに増やす。

	// 3) Jacobsthal 順に挿入
	for (size_t k = 0; k < order.size(); ++k) {
		size_t one_based = order[k];
		size_t idx = one_based - 1;               // pending の 0-based
		int to_insert = pending[idx];

		// 相棒（現ペンディングが属するペアの larger）とその現在位置
		int partner = (idx < sorted_pairs.size())
						? sorted_pairs[idx].larger
						: INT_MAX; // straggler のときは全域可

		size_t partner_pos = (idx < sorted_pairs.size())
								? locate_partner_pos(result, partner)
								: result.size();

		// one_basedが属するJacobsthalブロックを特定
		size_t jacobsthal_limit = 0;
		for (size_t i = 0; i < J.size(); ++i) {
			if (one_based <= J[i]) {
				jacobsthal_limit = J[i];
				break;
			}
		}

		// 探索上限：min(partner 位置, main_chain 初期長 + jacobsthal_limit)
		size_t main_chain_initial = sorted_pairs.size();
		size_t search_limit = main_chain_initial + jacobsthal_limit;
		size_t right = std::min(partner_pos, search_limit);

		// [0, right) で二分探索（比較は comp_count へカウント）
		
		size_t left = 0;
		while (left < right) {
			size_t mid = left + (right - left) / 2;
			comp_count++;
			if (result[mid] < to_insert) {
				left = mid + 1;
			} else {
				right = mid;
			}
		}
		result.insert(result.begin() + left, to_insert);
	}

	v = result;
}

// Ford–Johnson（merge-insertion）法の deque 実装。
// larger の整列は vector 実装を流用し、復元と挿入は deque の操作で行う。
static void ford_johnson_deque_impl(std::deque<int>& d, size_t& comp_count) {
	const size_t n = d.size();
	if (n <= 1) return;

	// 1) ペア化（vector 版と同様）
	std::deque<IndexedPair> pairs;
	bool has_straggler = (n % 2) != 0;
	int straggler = 0;

	for (size_t i = 0; i + 1 < n; i += 2) {
		comp_count++;
		if (d[i] > d[i + 1]) pairs.push_back(IndexedPair(d[i], d[i + 1], i / 2));
		else                 pairs.push_back(IndexedPair(d[i + 1], d[i], i / 2));
	}
	if (has_straggler) straggler = d[n - 1];
	if (pairs.empty()) return;

	// 2) larger 抽出 → （deque は vector 版を流用して）再帰整列
	std::vector<int> larger_values;
	larger_values.reserve(pairs.size());
	for (size_t i = 0; i < pairs.size(); ++i) larger_values.push_back(pairs[i].larger);

	ford_johnson_vector_impl(larger_values, comp_count);

	// 復元（重複OK）
	std::deque<IndexedPair> sorted_pairs;
	for (size_t i = 0; i < larger_values.size(); ++i) {
		int want = larger_values[i];
		for (size_t j = 0; j < pairs.size(); ++j) {
			if (pairs[j].larger == want) {
				sorted_pairs.push_back(pairs[j]);
				pairs[j].larger = INT_MIN;
				break;
			}
		}
	}

	// 初期 result = [全 larger]
	std::deque<int> result;
	for (size_t i = 0; i < sorted_pairs.size(); ++i) result.push_back(sorted_pairs[i].larger);

	// pending = 全ての smaller + straggler
	std::deque<int> pending;
	for (size_t i = 0; i < sorted_pairs.size(); ++i) pending.push_back(sorted_pairs[i].smaller);
	if (has_straggler) pending.push_back(straggler);
	if (pending.empty()) { d = result; return; }

	// Jacobsthal 順と J ブレーク
	const std::vector<size_t> J = make_jacobsthal_breaks(pending.size());
	const std::vector<size_t> order = make_jacobsthal_order(pending.size());

	// Jacobsthal に従って pending を二分探索で result へ挿入（deque 版）

	// 3) 挿入
	for (size_t k = 0; k < order.size(); ++k) {
		size_t one_based = order[k];
		size_t idx = one_based - 1;
		int to_insert = pending[idx];

		int partner = (idx < sorted_pairs.size())
						? sorted_pairs[idx].larger
						: INT_MAX;

		// partner の現在位置を線形に検索（deque）
		size_t partner_pos = result.size();
		if (idx < sorted_pairs.size()) {
			for (size_t i = 0; i < result.size(); ++i) {
				if (result[i] == partner) { partner_pos = i; break; }
			}
		}

		// one_basedが属するJacobsthalブロックを特定
		size_t jacobsthal_limit = 0;
		for (size_t i = 0; i < J.size(); ++i) {
			if (one_based <= J[i]) {
				jacobsthal_limit = J[i];
				break;
			}
		}

		// 探索上限：min(partner 位置, main_chain 初期長 + jacobsthal_limit)
		size_t main_chain_initial = sorted_pairs.size();
		size_t search_limit = main_chain_initial + jacobsthal_limit;
		size_t right = std::min(partner_pos, search_limit);

		
		size_t left = 0;
		while (left < right) {
			size_t mid = left + (right - left) / 2;
			comp_count++;
			if (result[mid] < to_insert) {
				left = mid + 1;
			} else {
				right = mid;
			}
		}
		result.insert(result.begin() + left, to_insert);
	}

	d = result;
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
