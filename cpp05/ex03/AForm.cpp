#include "AForm.hpp"
#include "Bureaucrat.hpp"

const char* AForm::GradeTooHighException::what() const throw()
{
	return "Grade too high";
}

const char* AForm::GradeTooLowException::what() const throw()
{
	return "Grade too low";
}

const char* AForm::AlreadySignedException::what() const throw()
{
	return "Form::Already signed";
}

const char* AForm::FormNotSignedException::what() const throw()
{
	return "Form is not signed";
}

AForm::AForm() : _name(""), _isSigned(false), _gradeToSign(1), _gradeToExecute(1)
{
}

AForm::AForm(const std::string &name, int gradeToSign, int gradeToExecute) : _name(name), _isSigned(false), _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute)
{
	if (gradeToSign < 1 || gradeToExecute < 1)
		throw AForm::GradeTooHighException();
	if (gradeToSign > 150 || gradeToExecute > 150)
		throw AForm::GradeTooLowException();
}

AForm::AForm(const AForm &other) : _name(other._name), _isSigned(other._isSigned), _gradeToSign(other._gradeToSign), _gradeToExecute(other._gradeToExecute)
{
}

AForm &AForm::operator=(const AForm &other)
{
	if (this != &other)
	{
		_isSigned = other._isSigned;
	}
	return *this;
}

AForm::~AForm()
{
}

const std::string &AForm::getName() const
{
	return this->_name;
}

bool AForm::getIsSigned() const
{
	return this->_isSigned;
}

int AForm::getGradeToSign() const
{
	return this->_gradeToSign;
}

int AForm::getGradeToExecute() const
{
	return this->_gradeToExecute;
}

void AForm::beSigned(const Bureaucrat &bureaucrat)
{
	if (this->_isSigned)
		throw AForm::AlreadySignedException();
	if (bureaucrat.getGrade() > this->_gradeToSign)
		throw AForm::GradeTooLowException();
	this->_isSigned = true;
}


void AForm::execute(const Bureaucrat &executor) const
{
	if (!this->getIsSigned())
		throw AForm::FormNotSignedException();
	if (executor.getGrade() > this->getGradeToExecute())
		throw AForm::GradeTooLowException();
	this->executeAction();
}

std::ostream &operator<<(std::ostream &os, const AForm &form)
{
	os << form.getName() << ", form grade to sign " << form.getGradeToSign() 
	   << ", form grade to execute " << form.getGradeToExecute()
	   << ", signed: " << (form.getIsSigned() ? "yes" : "no");
	return os;
}
