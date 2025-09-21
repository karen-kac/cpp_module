#include "Intern.hpp"
#include <stdexcept>
#include <iostream>

// コンストラクタ/デストラクタ
Intern::Intern() {}
Intern::Intern(const Intern& other) { (void)other; }
Intern& Intern::operator=(const Intern& other) { (void)other; return *this; }
Intern::~Intern() {}

// --- 各フォーム生成関数
static AForm* createShrubbery(const std::string& target) {
	return new ShrubberyCreationForm(target);
}

static AForm* createRobotomy(const std::string& target) {
	return new RobotomyRequestForm(target);
}

static AForm* createPresidential(const std::string& target) {
	return new PresidentialPardonForm(target);
}

AForm* Intern::makeForm(const std::string& name, const std::string& target) const
{
	static const int n = 3;
	const std::string formNames[n] = {
		"shrubbery creation",
		"robotomy request",
		"presidential pardon"
	};

	AForm* (*formCreators[n])(const std::string&) = {
		&createShrubbery,
		&createRobotomy,
		&createPresidential
	};

	for (int i = 0; i < n; i++)
	{
		if (name == formNames[i])
		{
			std::cout << "Intern creates " << name << std::endl;
			return formCreators[i](target);
		}
	}

	// 不明なフォーム名の場合は例外を投げる
	throw std::runtime_error("Intern: Unknown form name: " + name);
}
