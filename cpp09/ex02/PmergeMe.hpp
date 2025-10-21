#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <ctime>
#include <string>
#include <vector>
#include <deque>

class PmergeMe
{
	std::vector<int> vector_container;
	std::deque<int> deque_container;
private:
	clock_t _start;
	clock_t _end;
	mutable size_t _count;
	
	bool parseInt(char* s, int& out) const;
	void print_elements() const;
	void print_deque_elements() const;
	void print_elapsed_time(const char* container_label, size_t num_elements) const;
	void sort_ford_johnson_vector();
	void sort_ford_johnson_deque();
	bool load_container(char **argv);

public:
	PmergeMe();
	PmergeMe(const PmergeMe& other);
	PmergeMe& operator=(const PmergeMe &other);
	PmergeMe(int argc, char **argv);
	~PmergeMe();
	
	void run();
};

#endif
