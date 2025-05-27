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

	// インクリメント/デクリメント関数のテスト
	try {
		std::cout << "\n==== インクリメント/デクリメントテスト ====" << std::endl;
		Bureaucrat bob("Bob", 75);
		std::cout << "初期状態: " << bob << std::endl;
		
		bob.incrementGrade(); // 75 -> 74
		std::cout << "インクリメント後: " << bob << std::endl;
		
		bob.decrementGrade(); // 74 -> 75
		std::cout << "デクリメント後: " << bob << std::endl;
	}
	catch (std::exception &e) {
		std::cerr << "Caught exception: " << e.what() << std::endl;
	}

	try {
		std::cout << "\n==== Grade 1からのインクリメントで例外 ====" << std::endl;
		Bureaucrat topLevel("TopLevel", 1);
		std::cout << "インクリメント前: " << topLevel << std::endl;
		topLevel.incrementGrade(); // 例外発生
	}
	catch (std::exception &e) {
		std::cerr << "Caught exception: " << e.what() << std::endl;
	}

	try {
		std::cout << "\n==== Grade 150からのデクリメントで例外 ====" << std::endl;
		Bureaucrat bottomLevel("BottomLevel", 150);
		std::cout << "デクリメント前: " << bottomLevel << std::endl;
		bottomLevel.decrementGrade(); // 例外発生
	}
	catch (std::exception &e) {
		std::cerr << "Caught exception: " << e.what() << std::endl;
	}

	try {
		std::cout << "\n==== 境界値テスト（Grade 2からインクリメント） ====" << std::endl;
		Bureaucrat nearTop("NearTop", 2);
		std::cout << "インクリメント前: " << nearTop << std::endl;
		nearTop.incrementGrade(); // 2 -> 1（正常）
		std::cout << "インクリメント後: " << nearTop << std::endl;
	}
	catch (std::exception &e) {
		std::cerr << "Caught exception: " << e.what() << std::endl;
	}

	try {
		std::cout << "\n==== 境界値テスト（Grade 149からデクリメント） ====" << std::endl;
		Bureaucrat nearBottom("NearBottom", 149);
		std::cout << "デクリメント前: " << nearBottom << std::endl;
		nearBottom.decrementGrade(); // 149 -> 150（正常）
		std::cout << "デクリメント後: " << nearBottom << std::endl;
	}
	catch (std::exception &e) {
		std::cerr << "Caught exception: " << e.what() << std::endl;
	}

	return 0;
}