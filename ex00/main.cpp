#include "easyfind.hpp"
#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <iterator>

int main()
{
	// vectorでのテスト
	std::cout << "vectorでのテスト:" << std::endl;
	std::vector<int> vec;
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);
	vec.push_back(5);

	try {
		std::vector<int>::iterator it = easyfind(vec, 3);
		std::cout << "find: " << *it << std::endl;
		std::cout << "position: " << std::distance(vec.begin(), it) << std::endl;
	} catch(const std::exception& e) {
		std::cerr << "例外: " << e.what() << std::endl;
	}

	try {
		std::vector<int>::iterator it = easyfind(vec, 42);
		std::cout << "find: " << *it << std::endl;
	} catch(const std::exception& e) {
		std::cerr << "例外: " << e.what() << std::endl;
	}

	// listでのテスト
	std::cout << "\nlistでのテスト:" << std::endl;
	std::list<int> lst;
	lst.push_back(10);
	lst.push_back(20);
	lst.push_back(30);
	lst.push_back(40);

	try {
		std::list<int>::iterator it = easyfind(lst, 20);
		std::cout << "find: " << *it << std::endl;
		std::cout << "position: " << std::distance(lst.begin(), it) << std::endl;
	} catch(const std::exception& e) {
		std::cerr << "例外: " << e.what() << std::endl;
	}

	try {
		std::list<int>::iterator it = easyfind(lst, 100);
		std::cout << "find: " << *it << std::endl;
	} catch(const std::exception& e) {
		std::cerr << "例外: " << e.what() << std::endl;
	}

	// dequeでのテスト
	std::cout << "\ndequeでのテスト:" << std::endl;
	std::deque<int> deq;
	deq.push_back(5);
	deq.push_back(10);
	deq.push_back(15);

	try {
		std::deque<int>::iterator it = easyfind(deq, 10);
		std::cout << "find: " << *it << std::endl;
		std::cout << "position: " << std::distance(deq.begin(), it) << std::endl;
	} catch(const std::exception& e) {
		std::cerr << "例外: " << e.what() << std::endl;
	}

	// const vectorでのテスト
	std::cout << "\nconst vectorでのテスト:" << std::endl;
	const std::vector<int> const_vec(vec);

	try {
		std::vector<int>::const_iterator it = easyfind(const_vec, 4);
		std::cout << "find: " << *it << std::endl;
		std::cout << "position: " << std::distance(const_vec.begin(), it) << std::endl;
	} catch(const std::exception& e) {
		std::cerr << "例外: " << e.what() << std::endl;
	}

	return 0;
}
