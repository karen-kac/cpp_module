#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "Intern.hpp"

int main() {
	std::cout << "===== Exercise 03: Intern =====\n" << std::endl;

	try {
		Intern someRandomIntern;
		Bureaucrat boss("Boss", 1);

		// Shrubbery
		AForm* shrub = someRandomIntern.makeForm("shrubbery creation", "garden");
		boss.signForm(*shrub);
		boss.executeForm(*shrub);
		delete shrub;

		// Robotomy
		AForm* robot = someRandomIntern.makeForm("robotomy request", "Bender");
		boss.signForm(*robot);
		boss.executeForm(*robot);
		delete robot;

		// Presidential
		AForm* pardon = someRandomIntern.makeForm("presidential pardon", "Arthur Dent");
		boss.signForm(*pardon);
		boss.executeForm(*pardon);
		delete pardon;

		// 無効なフォーム名
		AForm* invalid = someRandomIntern.makeForm("invalid form", "target");
		delete invalid; // 到達しない
	}
	catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	return 0;
}
