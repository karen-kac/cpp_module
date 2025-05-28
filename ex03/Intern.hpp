#ifndef INTERN_HPP
#define INTERN_HPP

#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <string>

class Intern
{
	private:
		typedef AForm* (Intern::*FormCreator)(const std::string& target) const;
		
		struct FormInfo {
			std::string name;
			FormCreator creator;
		};
		
		AForm* createShrubberyCreationForm(const std::string& target) const;
		AForm* createRobotomyRequestForm(const std::string& target) const;
		AForm* createPresidentialPardonForm(const std::string& target) const;
		
		static const FormInfo* getFormInfo();
		static int getFormCount();

	public:
		Intern();
		Intern(const Intern& other);
		Intern& operator=(const Intern& other);
		~Intern();

		AForm* makeForm(const std::string& formName, const std::string& target) const;
};

#endif