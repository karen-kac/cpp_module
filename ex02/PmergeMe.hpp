#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <ctime>
#include <string>
#include <vector>
#include <deque>

class PmergeMe
{
	std::vector<int> container;
	std::deque<int> deque_container;
private:
	clock_t _start;
	clock_t _end;
	mutable size_t _count;
	
	PmergeMe(const PmergeMe& other);
	PmergeMe& operator=(const PmergeMe &other);
	
	bool parseInt(char* s, int& out) const;
	void print_elements() const;
	void print_elapsed_time() const;
	void sort_ford_johnson();
	void sort_ford_johnson_deque();
	bool load_container(char **argv);

public:
	PmergeMe();
	PmergeMe(int argc, char **argv);
	PmergeMe(char **argv);
	~PmergeMe();
	
	void run();
};

#endif
