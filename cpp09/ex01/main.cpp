#include "RPN.hpp"

int main(int argc, char** argv) {
	if (argc != 2) {
		std::cerr << "Error" << std::endl;
		return 1;
	}

	try {
		RPN rpn;
		int result = rpn.evaluate(argv[1]);
		std::cout << result << std::endl;
	} catch (std::exception& e) {
		std::cerr << "Error" << std::endl;
		return 1;
	}
	
	return 0;
}

// ./RPN "1 2 +"                     # 1 + 2 = 3
// ./RPN "5 1 -"                     # 5 - 1 = 4
// ./RPN "2 3 *"                     # 2 * 3 = 6
// ./RPN "8 4 /"                     # 8 / 4 = 2
// ./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +" # 複雑: = 42
// ./RPN "7 7 * 7 -"                 # = 42
// ./RPN "1 2 * 2 / 2 * 2 4 - +"     # = 0
// ./RPN "9 8 * 4 * 4 / 2 + 9 - 8 - 8 - 1 - 6 -" # = 42
// ./RPN "3 4 + 2 * 7 /"             # (3+4)*2/7 = 2
// ./RPN "9 3 / 2 * 5 +"             # 9/3=3, *2=6, +5=11
