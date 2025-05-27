#include "Bureaucrat.hpp"
#include "Form.hpp"

int main() {
	std::cout << "===== Exercise 01: Forms =====\n" << std::endl;

	try {
		std::cout << "==== フォームとビューロクラットの作成 ====" << std::endl;
		Bureaucrat alice("Alice", 50);
		Bureaucrat bob("Bob", 140);
		Form contract("NDA", 100, 50);

		std::cout << alice << std::endl;
		std::cout << bob << std::endl;
		std::cout << contract << std::endl;

		std::cout << "\n==== Bob (grade 140) がNDA (要求grade 100) に署名を試みる ====" << std::endl;
		bob.signForm(contract);  // 失敗する（140 > 100）

		std::cout << "\n==== Alice (grade 50) がNDA (要求grade 100) に署名を試みる ====" << std::endl;
		alice.signForm(contract);  // 成功する（50 <= 100）

		std::cout << "\n==== 署名後のフォーム状態 ====" << std::endl;
		std::cout << contract << std::endl;

		std::cout << "\n==== 既に署名されたフォームに再度署名 ====" << std::endl;
		alice.signForm(contract);  // 既に署名済み

	} catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	try {
		std::cout << "\n==== 無効なグレードでフォーム作成 ====" << std::endl;
		Form invalidForm("Invalid", 0, 50);  // 例外発生
	} catch (std::exception& e) {
		std::cerr << "Caught exception: " << e.what() << std::endl;
	}

	try {
		std::cout << "\n==== 無効なグレードでフォーム作成 (その2) ====" << std::endl;
		Form invalidForm2("Invalid2", 50, 151);  // 例外発生
	} catch (std::exception& e) {
		std::cerr << "Caught exception: " << e.what() << std::endl;
	}

	try {
		std::cout << "\n==== 境界値テスト ====" << std::endl;
		Bureaucrat topBureaucrat("TopBureaucrat", 1);
		Bureaucrat lowBureaucrat("LowBureaucrat", 150);
		Form strictForm("StrictForm", 1, 1);
		Form easyForm("EasyForm", 150, 150);

		std::cout << "\n--- Top bureaucrat (grade 1) が strict form (要求grade 1) に署名 ---" << std::endl;
		topBureaucrat.signForm(strictForm);

		std::cout << "\n--- Low bureaucrat (grade 150) が easy form (要求grade 150) に署名 ---" << std::endl;
		lowBureaucrat.signForm(easyForm);

		std::cout << "\n--- Low bureaucrat (grade 150) が strict form (要求grade 1) に署名を試みる ---" << std::endl;
		lowBureaucrat.signForm(strictForm);  // 失敗

	} catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	return 0;
}
