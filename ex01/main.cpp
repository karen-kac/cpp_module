#include "Bureaucrat.hpp"
#include "Form.hpp"

int main() {
	try {
		Bureaucrat alice("Alice", 50);
		Bureaucrat bob("Bob", 140);

		Form contract("NDA", 100, 50);

		std::cout << alice << std::endl;
		std::cout << bob << std::endl;
		std::cout << contract << std::endl;

		std::cout << "\n--- Bob tries to sign NDA ---" << std::endl;
		contract.beSigned(bob);  // 失敗する（140 > 100）

		std::cout << "\n--- Alice tries to sign NDA ---" << std::endl;
		contract.beSigned(alice);  // 成功する（50 <= 100）

		std::cout << "\n--- Final Form Status ---" << std::endl;
		std::cout << contract << std::endl;

	} catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	return 0;
}
