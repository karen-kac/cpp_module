#include "Bureaucrat.hpp"

int main() {
	try {
		std::cout << "==== 正常なBureaucratの作成 ====" << std::endl;
		Bureaucrat a("Alice", 42);
		std::cout << a << std::endl;

		std::cout << "\n==== Grade 1のBureaucrat ====" << std::endl;
		Bureaucrat top("TopGun", 1);
		std::cout << top << std::endl;

		std::cout << "\n==== Grade 150のBureaucrat ====" << std::endl;
		Bureaucrat low("LowMan", 150);
		std::cout << low << std::endl;

		std::cout << "\n==== Grade 0で例外発生 ====" << std::endl;
		Bureaucrat tooHigh("God", 0); // 例外発生
		std::cout << tooHigh << std::endl; // 実行されない
	}
	catch (std::exception &e) {
		std::cerr << "Caught exception: " << e.what() << std::endl;
	}

	try {
		std::cout << "\n==== Grade 151で例外発生 ====" << std::endl;
		Bureaucrat tooLow("Devil", 151); // 例外発生
	}
	catch (std::exception &e) {
		std::cerr << "Caught exception: " << e.what() << std::endl;
	}

	return 0;
}
