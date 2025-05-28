#include "Intern.hpp"
#include <iostream>

Intern::Intern()
{
}

Intern::Intern(const Intern& other)
{
	(void)other;
}

Intern& Intern::operator=(const Intern& other)
{
	(void)other;
	return *this;
}

Intern::~Intern()
{
}

AForm* Intern::createShrubberyCreationForm(const std::string& target) const
{
	return new ShrubberyCreationForm(target);
}

AForm* Intern::createRobotomyRequestForm(const std::string& target) const
{
	return new RobotomyRequestForm(target);
}

AForm* Intern::createPresidentialPardonForm(const std::string& target) const
{
	return new PresidentialPardonForm(target);
}

const Intern::FormInfo* Intern::getFormInfo()
{
	static const FormInfo formInfo[] = {
		{"shrubbery creation", &Intern::createShrubberyCreationForm},
		{"robotomy request", &Intern::createRobotomyRequestForm},
		{"presidential pardon", &Intern::createPresidentialPardonForm}
	};
	return formInfo;
}

int Intern::getFormCount()
{
	return 3;
}

AForm* Intern::makeForm(const std::string& formName, const std::string& target) const
{
	const FormInfo* forms = getFormInfo();
	const int count = getFormCount();
	
	// フォーム名を検索
	for (int i = 0; i < count; i++)
	{
		if (forms[i].name == formName)
		{
			std::cout << "Intern creates " << formName << std::endl;
			return (this->*(forms[i].creator))(target);
		}
	}
	
	// フォームが見つからない場合
	std::cout << "Error: Intern cannot create '" << formName 
	          << "' form because it doesn't exist" << std::endl;
	return NULL;
}