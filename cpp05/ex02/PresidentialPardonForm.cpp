#include "PresidentialPardonForm.hpp"
#include "Bureaucrat.hpp"

PresidentialPardonForm::PresidentialPardonForm() : AForm("PresidentialPardonForm", 25, 5), _target("default")
{
}

PresidentialPardonForm::PresidentialPardonForm(const std::string &target) 
	: AForm("PresidentialPardonForm", 25, 5), _target(target)
{
}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm &other) 
	: AForm(other), _target(other._target)
{
}

PresidentialPardonForm &PresidentialPardonForm::operator=(const PresidentialPardonForm &other)
{
	if (this != &other)
	{
		AForm::operator=(other);
		// _targetは定数なので代入できない
	}
	return *this;
}

PresidentialPardonForm::~PresidentialPardonForm()
{
}

const std::string &PresidentialPardonForm::getTarget() const
{
	return this->_target;
}

void PresidentialPardonForm::executeAction() const
{
	std::cout << this->_target << " has been pardoned by Zaphod Beeblebrox." << std::endl;
}