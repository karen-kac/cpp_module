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
bool PmergeMe::parseInt(char* s, int& out) const {
	char *endp;
	long val = std::strtol(s, &endp, 10);
	if (*endp != '\0' || val <= 0 || val > INT_MAX)
		return false;
	out = static_cast<int>(val);
	return true;
}

// Load
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
	for (std::vector<int>::const_iterator it = vector_container.begin(); 
		 it != vector_container.end() && count < max; ++it, ++count) {
		std::cout << (count ? " " : "") << *it;
	}
	if (vector_container.size() > max) std::cout << " [...]";
	std::cout << std::endl;
}

void PmergeMe::print_deque_elements() const {
	size_t count = 0;
	size_t max = 21;
	for (std::deque<int>::const_iterator it = deque_container.begin(); 
		 it != deque_container.end() && count < max; ++it, ++count) {
		std::cout << (count ? " " : "") << *it;
	}
	if (deque_container.size() > max) std::cout << " [...]";
	std::cout << std::endl;
}

// ===== Ford-Johnson Algorithm Core =====

// ペア構造体（値を直接保持）
struct ValuePair {
	int larger;
	int smaller;
	size_t original_order;
	
	ValuePair(int l, int s, size_t o) : larger(l), smaller(s), original_order(o) {}
};

// Jacobsthal数列生成: J(0)=0, J(1)=1, J(n)=J(n-1)+2*J(n-2)
static std::vector<size_t> generate_jacobsthal() {
	std::vector<size_t> seq;
	seq.push_back(0);
	seq.push_back(1);
	
	// 十分大きな値まで生成
	for (int i = 0; i < 20; ++i) {
		size_t next = seq[seq.size() - 1] + 2 * seq[seq.size() - 2];
		seq.push_back(next);
	}
	return seq;
}

// Jacobsthal挿入順序生成
static std::vector<size_t> generate_insertion_order(size_t n) {
	if (n == 0) return std::vector<size_t>();
	
	std::vector<size_t> order;
	std::vector<size_t> jacob = generate_jacobsthal();
	
	size_t k = 2;  // J(2)=1から開始
	size_t pos = 1;
	
	while (pos <= n) {
		// 次のJacobsthal数
		size_t next_jacob = (k < jacob.size()) ? jacob[k] : n + 1;
		if (next_jacob > n) next_jacob = n;
		
		// 前のJacobsthal数
		size_t prev_jacob = jacob[k - 1];
		
		// [prev_jacob+1, next_jacob]を降順で追加
		for (size_t i = next_jacob; i > prev_jacob && i <= n; --i) {
			order.push_back(i);
			pos++;
		}
		
		k++;
		if (next_jacob >= n) break;
	}
	
	return order;
}

// largerの現在位置を探す（比較カウントなし）
template <typename Container>
static size_t find_position(const Container& chain, int value) {
	for (size_t i = 0; i < chain.size(); ++i) {
		if (chain[i] == value) return i;
	}
	return chain.size();
}

// === Vector 実装 ===
static void ford_johnson_vector_impl(std::vector<int>& arr, size_t& comp_count) {
	const size_t n = arr.size();
	if (n <= 1) return;
	
	// 1. ペア化
	std::vector<ValuePair> pairs;
	bool has_straggler = (n % 2 == 1);
	int straggler = 0;
	
	for (size_t i = 0; i + 1 < n; i += 2) {
		comp_count++;
		if (arr[i] > arr[i + 1]) {
			pairs.push_back(ValuePair(arr[i], arr[i + 1], i / 2));
		} else {
			pairs.push_back(ValuePair(arr[i + 1], arr[i], i / 2));
		}
	}
	if (has_straggler) {
		straggler = arr[n - 1];
	}
	
	if (pairs.empty()) return;
	
	// 2. larger要素を抽出して再帰的にソート
	std::vector<int> larger_chain;
	larger_chain.reserve(pairs.size());
	for (size_t i = 0; i < pairs.size(); ++i) {
		larger_chain.push_back(pairs[i].larger);
	}
	
	ford_johnson_vector_impl(larger_chain, comp_count);
	
	// 3. ソート後のlargerに基づいてペアを並び替え
	std::vector<ValuePair> sorted_pairs;
	sorted_pairs.reserve(pairs.size());
	std::vector<bool> used(pairs.size(), false);
	
	for (size_t i = 0; i < larger_chain.size(); ++i) {
		int target = larger_chain[i];
		// まだ使われていない一致する最初のペアを探す
		for (size_t j = 0; j < pairs.size(); ++j) {
			if (!used[j] && pairs[j].larger == target) {
				sorted_pairs.push_back(pairs[j]);
				used[j] = true;
				break;
			}
		}
	}
	
	// 4. Main chain構築（ソート済みのlargerのみ）
	std::vector<int> main_chain;
	main_chain.reserve(n);
	for (size_t i = 0; i < sorted_pairs.size(); ++i) {
		main_chain.push_back(sorted_pairs[i].larger);
	}
	
	// 5. 最初のsmallerを先頭に挿入（比較不要）
	if (!sorted_pairs.empty()) {
		main_chain.insert(main_chain.begin(), sorted_pairs[0].smaller);
	}
	
	// 6. 残りのsmallerとstragglerを準備
	std::vector<int> pending;
	std::vector<int> pending_partners;  // 対応するlargerの値
	
	for (size_t i = 1; i < sorted_pairs.size(); ++i) {
		pending.push_back(sorted_pairs[i].smaller);
		pending_partners.push_back(sorted_pairs[i].larger);
	}
	
	if (has_straggler) {
		pending.push_back(straggler);
		pending_partners.push_back(INT_MAX);  // stragglerは制約なし
	}
	
	if (pending.empty()) {
		arr = main_chain;
		return;
	}
	
	// 7. Jacobsthal順序で挿入
	std::vector<size_t> insertion_order = generate_insertion_order(pending.size());
	
	for (size_t k = 0; k < insertion_order.size(); ++k) {
		size_t idx = insertion_order[k] - 1;  // 1-basedから0-basedへ
		int to_insert = pending[idx];
		int partner = pending_partners[idx];
		
		// 探索範囲の上限：partnerの現在位置
		size_t upper_limit = main_chain.size();
		if (partner != INT_MAX) {
			upper_limit = find_position(main_chain, partner);
		}
		
		// 二分探索
		size_t left = 0;
		size_t right = upper_limit;
		
		while (left < right) {
			size_t mid = left + (right - left) / 2;
			comp_count++;
			if (main_chain[mid] < to_insert) {
				left = mid + 1;
			} else {
				right = mid;
			}
		}
		
		main_chain.insert(main_chain.begin() + left, to_insert);
	}
	
	arr = main_chain;
}

// === Deque 実装 ===
static void ford_johnson_deque_impl(std::deque<int>& arr, size_t& comp_count) {
	const size_t n = arr.size();
	if (n <= 1) return;
	
	// 1. ペア化
	std::vector<ValuePair> pairs;
	bool has_straggler = (n % 2 == 1);
	int straggler = 0;
	
	for (size_t i = 0; i + 1 < n; i += 2) {
		comp_count++;
		if (arr[i] > arr[i + 1]) {
			pairs.push_back(ValuePair(arr[i], arr[i + 1], i / 2));
		} else {
			pairs.push_back(ValuePair(arr[i + 1], arr[i], i / 2));
		}
	}
	if (has_straggler) {
		straggler = arr[n - 1];
	}
	
	if (pairs.empty()) return;
	
	// 2. larger要素を抽出（vectorで処理）
	std::vector<int> larger_chain;
	larger_chain.reserve(pairs.size());
	for (size_t i = 0; i < pairs.size(); ++i) {
		larger_chain.push_back(pairs[i].larger);
	}
	
	ford_johnson_vector_impl(larger_chain, comp_count);
	
	// 3. ペアを並び替え
	std::vector<ValuePair> sorted_pairs;
	sorted_pairs.reserve(pairs.size());
	std::vector<bool> used(pairs.size(), false);
	
	for (size_t i = 0; i < larger_chain.size(); ++i) {
		int target = larger_chain[i];
		for (size_t j = 0; j < pairs.size(); ++j) {
			if (!used[j] && pairs[j].larger == target) {
				sorted_pairs.push_back(pairs[j]);
				used[j] = true;
				break;
			}
		}
	}
	
	// 4. Main chain構築
	std::deque<int> main_chain;
	for (size_t i = 0; i < sorted_pairs.size(); ++i) {
		main_chain.push_back(sorted_pairs[i].larger);
	}
	
	// 5. 最初のsmallerを先頭に挿入
	if (!sorted_pairs.empty()) {
		main_chain.push_front(sorted_pairs[0].smaller);
	}
	
	// 6. 残りのsmallerとstragglerを準備
	std::vector<int> pending;
	std::vector<int> pending_partners;
	
	for (size_t i = 1; i < sorted_pairs.size(); ++i) {
		pending.push_back(sorted_pairs[i].smaller);
		pending_partners.push_back(sorted_pairs[i].larger);
	}
	
	if (has_straggler) {
		pending.push_back(straggler);
		pending_partners.push_back(INT_MAX);
	}
	
	if (pending.empty()) {
		arr = main_chain;
		return;
	}
	
	// 7. Jacobsthal順序で挿入
	std::vector<size_t> insertion_order = generate_insertion_order(pending.size());
	
	for (size_t k = 0; k < insertion_order.size(); ++k) {
		size_t idx = insertion_order[k] - 1;
		int to_insert = pending[idx];
		int partner = pending_partners[idx];
		
		// 探索範囲の上限
		size_t upper_limit = main_chain.size();
		if (partner != INT_MAX) {
			upper_limit = find_position(main_chain, partner);
		}
		
		// 二分探索
		size_t left = 0;
		size_t right = upper_limit;
		
		while (left < right) {
			size_t mid = left + (right - left) / 2;
			comp_count++;
			if (main_chain[mid] < to_insert) {
				left = mid + 1;
			} else {
				right = mid;
			}
		}
		
		main_chain.insert(main_chain.begin() + left, to_insert);
	}
	
	arr = main_chain;
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
	
	std::cout << "\n=== Vector ===" << std::endl;
	sort_ford_johnson_vector();
	std::cout << "After: ";
	print_elements();
	print_elapsed_time();
	std::cout << "比較回数 : " << _count << std::endl;
	
	std::cout << "\n=== Deque ===" << std::endl;
	sort_ford_johnson_deque();
	std::cout << "After: ";
	print_deque_elements();
	print_elapsed_time();
	std::cout << "比較回数 : " << _count << std::endl;
}
