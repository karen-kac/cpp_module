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
#include <cstdlib>

PmergeMe::PmergeMe() : _count(0) {}

PmergeMe::PmergeMe(char **argv) : _count(0) {
	if (!load_container(argv))
		throw std::runtime_error("Error");
}

PmergeMe::PmergeMe(int argc, char **argv) : _count(0) {
	(void)argc;
	if (!load_container(argv))
		throw std::runtime_error("Error: Fail to load cotent");
}

PmergeMe::PmergeMe(const PmergeMe& other) { (void) other; }

PmergeMe& PmergeMe::operator=(const PmergeMe &other) {
	(void) other;
	return *this;
}

PmergeMe::~PmergeMe() {}



bool PmergeMe::parseInt(char* s, int& out) const {
	char *endp;
	long val = std::strtol(s, &endp, 10);
	if (*endp != '\0' || val <= 0 || val > INT_MAX)
		return false;
	out = static_cast<int>(val);
	return true;
}

bool PmergeMe::load_container(char **argv) {
	for (int i = 1; argv[i]; ++i) {
		int x;
		if (!parseInt(argv[i], x)) {
			std::cerr << "Error: only positive integer accepted." << std::endl;
			return false;
		}
		container.push_back(x);
		deque_container.push_back(x);
	}
	return true;
}

void PmergeMe::print_elapsed_time() const {
	double elapsed_time = static_cast<double>(_end - _start) / CLOCKS_PER_SEC * 1e6;
	std::cout	<< "Time to process a range of " << container.size()
				<< " elements : " 
				<< std::fixed << std::setprecision(6) << elapsed_time
				<< " us" << std::endl;
}

void PmergeMe::print_elements() const {
	
	size_t count = 0;
	size_t max = 4;
	for (std::vector<int>::const_iterator it = container.begin(); it != container.end() && count < max; ++it, ++count) {
		std::cout << (count ? " " : "") << *it;
	}
	if (container.size() > max) std::cout << " [...]";
	std::cout << std::endl;
}


static void ford_johnson(std::vector<int>& v, size_t& comp_count) {
	const size_t n = v.size();
	if (n <= 1) return;
	

	std::vector<int> pair_larger;
	std::vector<int> pair_smaller;
	bool is_odd = (n % 2) != 0;
	int odd_val = 0;
	for (size_t i = 0; i + 1 < n; i+=2) {
		int a = v[i];
		int b = v[i + 1];
		comp_count++;
		if (a > b) { pair_larger.push_back(a); pair_smaller.push_back(b); }
		else { pair_larger.push_back(b); pair_smaller.push_back(a); }
	}
	if (is_odd) odd_val = v[n - 1];

	std::vector<int> main_chain;
	for (size_t i = 0; i < pair_larger.size(); ++i)
		main_chain.push_back(pair_larger[i]);

	ford_johnson(main_chain, comp_count);

	std::vector<int> result;
	if (!main_chain.empty()) {
		for (size_t i = 0; i < pair_larger.size(); ++i) {
			if (pair_larger[i] == main_chain[0]) {
				result.push_back(pair_smaller[i]);
				break;
			}
		}
		result.push_back(main_chain[0]);
	}
	
	std::vector<int> pending_values;
	std::vector<size_t> pending_pair_idx; // 元のペアインデックス
	for (size_t i = 0; i < main_chain.size(); ++i) {
		for (size_t j = 0; j < pair_larger.size(); ++j) {
			if (pair_larger[j] == main_chain[i]) {
				pending_values.push_back(pair_smaller[j]);
				pending_pair_idx.push_back(j);
				break;
			}
		}
	}
	if (is_odd) {
		pending_values.push_back(odd_val);
		pending_pair_idx.push_back(pair_larger.size());
	}

	std::vector<size_t> insertion_order;
	{
		const size_t m = pending_values.size();
		if (m > 0) {
			std::vector<int> added;
			for (size_t i = 0; i < m; ++i) added.push_back(0);

			std::vector<size_t> jacobsthal_nums;
			for (int k = 3; ; ++k) {
				double val = (std::pow(2.0, static_cast<double>(k)) - std::pow(-1.0, static_cast<double>(k))) / 3.0;
				int jk = static_cast<int>(val + 0.5);
				if (jk > static_cast<int>(m)) break;
				jacobsthal_nums.push_back(static_cast<size_t>(jk));
			}

			insertion_order.push_back(0);
			added[0] = 1;
			size_t current_pos = 1;
			for (size_t i = 0; i < jacobsthal_nums.size(); ++i) {
				size_t jk = jacobsthal_nums[i];
				for (size_t idx = std::min(jk, m); idx-- > current_pos; ) {
					if (!added[idx]) {
						insertion_order.push_back(idx);
						added[idx] = 1;
					}
				}
				current_pos = jk;
			}
			for (size_t i = 0; i < m; ++i) {
				if (!added[i]) insertion_order.push_back(i);
			}
		}
	}

	for (size_t i = 1; i < main_chain.size(); ++i) {
		result.push_back(main_chain[i]);
	}

	for (size_t i = 0; i < insertion_order.size(); ++i) {
		size_t idx = insertion_order[i];
		if (idx < pending_values.size()) {
			int element = pending_values[idx];
			size_t pair_idx = pending_pair_idx[idx];
			
			size_t main_chain_0_idx = static_cast<size_t>(-1);
			for (size_t j = 0; j < pair_larger.size(); ++j) {
				if (pair_larger[j] == main_chain[0]) { main_chain_0_idx = j; break; }
			}
			if (pair_idx == main_chain_0_idx) {
				continue;
			}
			
			if (pair_idx == pair_larger.size()) {
				std::vector<int>::iterator left = result.begin();
				std::vector<int>::iterator right = result.end();
				if (left >= right) {
					result.push_back(element);
				} else {
					while (left < right) {
						std::vector<int>::iterator mid = left + (right - left) / 2;
						comp_count++;
						if (*mid < element) left = mid + 1; else right = mid;
					}
					result.insert(left, element);
				}
				continue;
			}
			

			std::vector<int>::iterator partner_pos = result.end();
			for (std::vector<int>::iterator it = result.begin(); it != result.end(); ++it) {
				if (*it == pair_larger[pair_idx]) { partner_pos = it; break; }
			}
			
			std::vector<int>::iterator left = result.begin();
			std::vector<int>::iterator right = partner_pos;
			if (left >= right || right > result.end()) { left = result.begin(); right = result.end(); }
			
			while (left < right) {
				std::vector<int>::iterator mid = left + (right - left) / 2;
				comp_count++;
				if (*mid < element) left = mid + 1; else right = mid;
			}
			result.insert(left, element);
		}
	}
	v.assign(result.begin(), result.end());
}

static void ford_johnson_deque(std::deque<int>& d, size_t& comp_count) {
	const size_t n = d.size();
	if (n <= 1) return;
	

	std::deque<int> pair_larger;
	std::deque<int> pair_smaller;
	bool is_odd = (n % 2) != 0;
	int odd_val = 0;
	for (size_t i = 0; i + 1 < n; i+=2) {
		int a = d[i];
		int b = d[i + 1];
		comp_count++;
		if (a > b) { pair_larger.push_back(a); pair_smaller.push_back(b); }
		else { pair_larger.push_back(b); pair_smaller.push_back(a); }
	}
	if (is_odd) odd_val = d[n - 1];


	std::deque<int> main_chain;
	for (size_t i = 0; i < pair_larger.size(); ++i)
		main_chain.push_back(pair_larger[i]);
	
	ford_johnson_deque(main_chain, comp_count);

	std::deque<int> result;

	if (!main_chain.empty()) {
		for (size_t i = 0; i < pair_larger.size(); ++i) {
			if (pair_larger[i] == main_chain[0]) {
				result.push_back(pair_smaller[i]);
				break;
			}
		}
		result.push_back(main_chain[0]);
	}
	

	std::deque<int> pending_values;
	std::deque<size_t> pending_pair_idx; // 元のペアインデックス
	for (size_t i = 0; i < main_chain.size(); ++i) {
		for (size_t j = 0; j < pair_larger.size(); ++j) {
			if (pair_larger[j] == main_chain[i]) {
				pending_values.push_back(pair_smaller[j]);
				pending_pair_idx.push_back(j);
				break;
			}
		}
	}

	if (is_odd) {
		pending_values.push_back(odd_val);
		pending_pair_idx.push_back(pair_larger.size());
	}


	std::deque<size_t> insertion_order;
	{
		const size_t m = pending_values.size();
		if (m > 0) {
			std::deque<int> added;
			for (size_t i = 0; i < m; ++i) added.push_back(0);

			std::deque<size_t> jacobsthal_nums;
			for (int k = 3; ; ++k) {
				double val = (std::pow(2.0, static_cast<double>(k)) - std::pow(-1.0, static_cast<double>(k))) / 3.0;
				int jk = static_cast<int>(val + 0.5);
				if (jk > static_cast<int>(m)) break;
				jacobsthal_nums.push_back(static_cast<size_t>(jk));
			}

			insertion_order.push_back(0);
			added[0] = 1;
			size_t current_pos = 1;
			for (size_t i = 0; i < jacobsthal_nums.size(); ++i) {
				size_t jk = jacobsthal_nums[i];
				for (size_t idx = std::min(jk, m); idx-- > current_pos; ) {
					if (!added[idx]) {
						insertion_order.push_back(idx);
						added[idx] = 1;
					}
				}
				current_pos = jk;
			}
			for (size_t i = 0; i < m; ++i) {
				if (!added[i]) insertion_order.push_back(i);
			}
		}
	}

	
	for (size_t i = 1; i < main_chain.size(); ++i) {
		result.push_back(main_chain[i]);
	}

	for (size_t i = 0; i < insertion_order.size(); ++i) {
		size_t idx = insertion_order[i];
		if (idx < pending_values.size()) {
			int element = pending_values[idx];
			size_t pair_idx = pending_pair_idx[idx];
			
			size_t main_chain_0_idx = static_cast<size_t>(-1);
			for (size_t j = 0; j < pair_larger.size(); ++j) {
				if (pair_larger[j] == main_chain[0]) { main_chain_0_idx = j; break; }
			}
			if (pair_idx == main_chain_0_idx) {
				continue;
			}
			
			if (pair_idx == pair_larger.size()) {
				std::deque<int>::iterator left = result.begin();
				std::deque<int>::iterator right = result.end();
				if (left >= right) {
					result.push_back(element);
				} else {
					while (left < right) {
						std::deque<int>::iterator mid = left + (right - left) / 2;
						comp_count++;
						if (*mid < element) left = mid + 1; else right = mid;
					}
					result.insert(left, element);
				}
				continue;
			}
			
			std::deque<int>::iterator partner_pos = result.end();
			for (std::deque<int>::iterator it = result.begin(); it != result.end(); ++it) {
				if (*it == pair_larger[pair_idx]) { partner_pos = it; break; }
			}
			
			std::deque<int>::iterator left = result.begin();
			std::deque<int>::iterator right = partner_pos;
			if (left >= right || right > result.end()) { left = result.begin(); right = result.end(); }
			
			while (left < right) {
				std::deque<int>::iterator mid = left + (right - left) / 2;
				comp_count++;
				if (*mid < element) left = mid + 1; else right = mid;
			}
			result.insert(left, element);
		}
	}


	d.assign(result.begin(), result.end());
}


void PmergeMe::sort_ford_johnson() {
	_start = std::clock();
	_count = 0;
	const size_t n = container.size();
	if (n <= 1) {
		_end = std::clock();
		return;
	}
	ford_johnson(container, _count);
	_end = std::clock();
}

void PmergeMe::sort_ford_johnson_deque() {
	_start = std::clock();
	_count = 0;
	const size_t n = deque_container.size();
	if (n <= 1) {
		_end = std::clock();
		return;
	}
	ford_johnson_deque(deque_container, _count);
	_end = std::clock();
}

void PmergeMe::run() {
	std::cout << "Before: ";
	print_elements();
	
	// Vectorでのソート
	std::cout << "\n=== Vector ===" << std::endl;
	sort_ford_johnson();
	std::cout << "After: ";
	print_elements();
	print_elapsed_time();
	std::cout << "比較回数 : " << _count << std::endl;
	
	// Dequeでのソート
	std::cout << "\n=== Deque ===" << std::endl;
	sort_ford_johnson_deque();
	std::cout << "After: ";
	print_elements();
	print_elapsed_time();
	std::cout << "比較回数 : " << _count << std::endl;
}
