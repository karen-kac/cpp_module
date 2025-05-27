#include "Form.hpp"
#include "Bureaucrat.hpp"

Form::Form() : _name(""), _isSigned(false), _gradeToSign(1), _gradeToExecute(1)
{
}

Form::Form(const std::string &name, int gradeToSign, int gradeToExecute) : _name(name), _isSigned(false), _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute)
{
	if (gradeToSign < 1 || gradeToExecute < 1)
		throw Form::GradeTooHighException();
	if (gradeToSign > 150 || gradeToExecute > 150)
		throw Form::GradeTooLowException();
}

Form::Form(const Form &other) : _name(other._name), _isSigned(other._isSigned), _gradeToSign(other._gradeToSign), _gradeToExecute(other._gradeToExecute)
{
}

Form &Form::operator=(const Form &other)
{
	if (this != &other)
	{
		_isSigned = other._isSigned;
	}
	return *this;
}

Form::~Form()
{
}

const std::string &Form::getName() const
{
	return this->_name;
}

bool Form::getIsSigned() const
{
	return this->_isSigned;
}

int Form::getGradeToSign() const
{
	return this->_gradeToSign;
}

int Form::getGradeToExecute() const
{
	return this->_gradeToExecute;
}

int Form::beSigned(const Bureaucrat &bureaucrat)
{
	if (this->_isSigned)
	{
		std::cout << this->_name << " is already signed" << std::endl;
		return 1;
	}
	if (bureaucrat.getGrade() > this->_gradeToSign)
		throw Form::GradeTooLowException();
	this->_isSigned = true;
	return 0;
}

std::ostream &operator<<(std::ostream &os, const Form &form)
{
	os << form.getName() << ", form grade to sign " << form.getGradeToSign() 
	   << ", form grade to execute " << form.getGradeToExecute()
	   << ", signed: " << (form.getIsSigned() ? "yes" : "no");
	return os;
}
