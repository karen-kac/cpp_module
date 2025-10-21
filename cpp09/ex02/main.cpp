#include "PmergeMe.hpp"
#include <iostream>

int main(int argc, char** argv) {
	if (argc < 2) {
		std::cerr << "Error : no arguments\n";
		return 1;
	}
	try {
		PmergeMe p(argc, argv);
		p.run();
	} catch (const std::exception& e) {
		std::cerr << e.what() << "\n";
		return 1;
	}
	return 0;
}
