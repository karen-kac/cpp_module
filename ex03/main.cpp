#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "Intern.hpp"

int main() {
	std::cout << "===== Exercise 03: Intern =====\n" << std::endl;

	try {
		// インターンとビューロクラットの作成
		std::cout << "==== インターンとビューロクラットの作成 ====" << std::endl;
		Intern someRandomIntern;
		Bureaucrat executor("Executor", 1);
		std::cout << executor << std::endl;

		std::cout << "\n==== 有効なフォーム作成テスト ====" << std::endl;
		
		// 1. Shrubbery Creation Form
		std::cout << "\n--- Shrubbery Creation Form ---" << std::endl;
		AForm* shrubberyForm = someRandomIntern.makeForm("shrubbery creation", "garden");
		if (shrubberyForm) {
			std::cout << *shrubberyForm << std::endl;
			executor.signForm(*shrubberyForm);
			executor.executeForm(*shrubberyForm);
			delete shrubberyForm;
		}

		// 2. Robotomy Request Form (PDFの例に従う)
		std::cout << "\n--- Robotomy Request Form ---" << std::endl;
		AForm* rrf = someRandomIntern.makeForm("robotomy request", "Bender");
		if (rrf) {
			std::cout << *rrf << std::endl;
			executor.signForm(*rrf);
			executor.executeForm(*rrf);
			delete rrf;
		}

		// 3. Presidential Pardon Form
		std::cout << "\n--- Presidential Pardon Form ---" << std::endl;
		AForm* pardonForm = someRandomIntern.makeForm("presidential pardon", "Arthur Dent");
		if (pardonForm) {
			std::cout << *pardonForm << std::endl;
			executor.signForm(*pardonForm);
			executor.executeForm(*pardonForm);
			delete pardonForm;
		}

		std::cout << "\n==== 無効なフォーム名テスト ====" << std::endl;
		
		// 存在しないフォーム名
		std::cout << "\n--- 存在しないフォーム名 ---" << std::endl;
		AForm* invalidForm1 = someRandomIntern.makeForm("invalid form", "target");
		if (invalidForm1) {
			delete invalidForm1;  // このブロックは実行されないはず
		}

		// 似ているが正確でない名前
		std::cout << "\n--- 似ているが正確でない名前 ---" << std::endl;
		AForm* invalidForm2 = someRandomIntern.makeForm("Shrubbery Creation", "target"); // 大文字小文字違い
		if (invalidForm2) {
			delete invalidForm2;  // このブロックは実行されないはず
		}

		AForm* invalidForm3 = someRandomIntern.makeForm("robotomy", "target"); // 省略形
		if (invalidForm3) {
			delete invalidForm3;  // このブロックは実行されないはず
		}

		std::cout << "\n==== インターンの複数利用テスト ====" << std::endl;
		
		// 複数のインターンが同じフォームを作成
		Intern intern1;
		Intern intern2;
		Intern intern3;

		std::cout << "\n--- 複数インターンによる同一フォーム作成 ---" << std::endl;
		AForm* form1 = intern1.makeForm("shrubbery creation", "office");
		AForm* form2 = intern2.makeForm("robotomy request", "Employee");
		AForm* form3 = intern3.makeForm("presidential pardon", "Citizen");

		if (form1 && form2 && form3) {
			std::cout << "All forms created successfully:" << std::endl;
			std::cout << "- " << form1->getName() << " for " << static_cast<ShrubberyCreationForm*>(form1)->getTarget() << std::endl;
			std::cout << "- " << form2->getName() << " for " << static_cast<RobotomyRequestForm*>(form2)->getTarget() << std::endl;
			std::cout << "- " << form3->getName() << " for " << static_cast<PresidentialPardonForm*>(form3)->getTarget() << std::endl;
			
			delete form1;
			delete form2;
			delete form3;
		}

		std::cout << "\n==== インターンによるフォーム大量生産テスト ====" << std::endl;
		
		// 同じインターンが複数のフォームを作成
		const int formCount = 6;
		AForm* forms[formCount];
		const char* formNames[] = {"shrubbery creation", "robotomy request", "presidential pardon"};
		const char* targets[] = {"location1", "target1", "person1", "location2", "target2", "person2"};
		
		std::cout << "\n--- 6つのフォームを連続作成 ---" << std::endl;
		for (int i = 0; i < formCount; i++) {
			forms[i] = someRandomIntern.makeForm(formNames[i % 3], targets[i]);
			if (forms[i]) {
				std::cout << "Created: " << forms[i]->getName() << std::endl;
			}
		}

		// 作成されたフォームをすべて実行
		std::cout << "\n--- 作成されたフォームの一括実行 ---" << std::endl;
		for (int i = 0; i < formCount; i++) {
			if (forms[i]) {
				executor.signForm(*forms[i]);
				executor.executeForm(*forms[i]);
				delete forms[i];
				std::cout << "---" << std::endl;
			}
		}

	} catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n==== メモリ管理テスト ====" << std::endl;
	
	// NULLチェックの重要性を示す
	try {
		Intern testIntern;
		AForm* nullForm = testIntern.makeForm("nonexistent", "target");
		
		std::cout << "--- NULL フォームの安全な処理 ---" << std::endl;
		if (nullForm) {
			std::cout << "Form created: " << nullForm->getName() << std::endl;
			delete nullForm;
		} else {
			std::cout << "No form was created (NULL returned)" << std::endl;
		}
		
	} catch (std::exception& e) {
		std::cerr << "Exception in memory management test: " << e.what() << std::endl;
	}

	return 0;
}
