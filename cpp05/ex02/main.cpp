#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int main() {
	std::cout << "===== Exercise 02: Concrete Forms =====\n" << std::endl;

	// ビューロクラットの作成
	try {
		std::cout << "==== ビューロクラットの作成 ====" << std::endl;
		Bureaucrat president("President", 1);        // すべて実行可能
		Bureaucrat manager("Manager", 50);           // 一部実行可能
		Bureaucrat senior("Senior", 40);             // Robot Form実行可能
		Bureaucrat intern("Intern", 150);            // 実行不可

		std::cout << president << std::endl;
		std::cout << manager << std::endl;
		std::cout << senior << std::endl;
		std::cout << intern << std::endl;

		std::cout << "\n==== ShrubberyCreationForm テスト ====" << std::endl;
		ShrubberyCreationForm shrub("garden");
		std::cout << shrub << std::endl;

		// 署名テスト (要求grade: 145)
		std::cout << "\n--- Manager (grade 50) がShrub Formに署名 ---" << std::endl;
		manager.signForm(shrub);

		// 実行テスト (要求grade: 137)
		std::cout << "\n--- Manager (grade 50) がShrub Formを実行 ---" << std::endl;
		manager.executeForm(shrub);

		std::cout << "\n--- Intern (grade 150) がShrub Formを実行しようとする ---" << std::endl;
		intern.executeForm(shrub);

		std::cout << "\n==== RobotomyRequestForm テスト ====" << std::endl;
		RobotomyRequestForm robot("Bender");
		std::cout << robot << std::endl;

		// 署名テスト (要求grade: 72)
		std::cout << "\n--- Manager (grade 50) がRobot Formに署名 ---" << std::endl;
		manager.signForm(robot);

		// 実行テスト (要求grade: 45)
		std::cout << "\n--- Senior (grade 40) がRobot Formを実行 ---" << std::endl;
		senior.executeForm(robot);

		// 複数回実行してランダム性を確認
		std::cout << "\n--- 再度Robot Formを実行（ランダム性確認） ---" << std::endl;
		senior.executeForm(robot);

		std::cout << "\n==== PresidentialPardonForm テスト ====" << std::endl;
		PresidentialPardonForm pardon("Arthur Dent");
		std::cout << pardon << std::endl;

		// 署名テスト (要求grade: 25)
		std::cout << "\n--- President (grade 1) がPardon Formに署名 ---" << std::endl;
		president.signForm(pardon);

		// 実行テスト (要求grade: 5)
		std::cout << "\n--- President (grade 1) がPardon Formを実行 ---" << std::endl;
		president.executeForm(pardon);

		std::cout << "\n--- Manager (grade 50) がPardon Formを実行しようとする ---" << std::endl;
		manager.executeForm(pardon);

	} catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n==== 未署名フォームの実行テスト ====" << std::endl;
	try {
		ShrubberyCreationForm unsignedForm("test");
		Bureaucrat highGrade("HighGrade", 1);
		
		std::cout << "--- 未署名フォームの実行を試みる ---" << std::endl;
		highGrade.executeForm(unsignedForm);
	} catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n==== グレード不足でのフォーム署名テスト ====" << std::endl;
	try {
		PresidentialPardonForm highLevelForm("VIP");
		Bureaucrat lowGrade("LowGrade", 100);
		
		std::cout << "--- Grade 100のビューロクラットが Presidential Form (要求grade 25) に署名を試みる ---" << std::endl;
		lowGrade.signForm(highLevelForm);
	} catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n==== ポリモーフィズムテスト ====" << std::endl;
	try {
		Bureaucrat executor("Executor", 1);
		
		// AForm*配列でポリモーフィズムを確認
		AForm* forms[3];
		forms[0] = new ShrubberyCreationForm("poly_garden");
		forms[1] = new RobotomyRequestForm("poly_robot");
		forms[2] = new PresidentialPardonForm("poly_pardon");

		for (int i = 0; i < 3; i++) {
			std::cout << "\n--- Form " << i + 1 << ": " << forms[i]->getName() << " ---" << std::endl;
			executor.signForm(*forms[i]);
			executor.executeForm(*forms[i]);
		}

		// メモリ解放
		for (int i = 0; i < 3; i++) {
			delete forms[i];
		}

	} catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	return 0;
}
