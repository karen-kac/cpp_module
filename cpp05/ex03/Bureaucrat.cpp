#include "Bureaucrat.hpp"
#include "AForm.hpp"

const char* Bureaucrat::GradeTooHighException::what() const throw()
{
	return "Grade too high";
}

const char* Bureaucrat::GradeTooLowException::what() const throw()
{
	return "Grade too low";
}

Bureaucrat::Bureaucrat() : _name(""), _grade(150)
{
}

Bureaucrat::Bureaucrat(const std::string &name, int grade) : _name(name), _grade(grade)
{
	if (grade < 1)
		throw Bureaucrat::GradeTooHighException();
	if (grade > 150)
		throw Bureaucrat::GradeTooLowException();
}

Bureaucrat::Bureaucrat(const Bureaucrat &other) : _name(other._name), _grade(other._grade)
{
}

Bureaucrat &Bureaucrat::operator=(const Bureaucrat &other)
{
	if (this != &other)
		_grade = other._grade;
	return *this;
}

Bureaucrat::~Bureaucrat()
{
}

const std::string &Bureaucrat::getName() const
{
	return this->_name;
}

int Bureaucrat::getGrade() const
{
	return this->_grade;
}

void Bureaucrat::incrementGrade()
{
	if (this->_grade <= 1)
		throw Bureaucrat::GradeTooHighException();
	this->_grade--;
}

void Bureaucrat::decrementGrade()
{
	if (this->_grade >= 150)
		throw Bureaucrat::GradeTooLowException();
	this->_grade++;
}

void Bureaucrat::signForm(AForm &form)
{
	try {
		form.beSigned(*this);
		std::cout << getName() << " signed " << form.getName() << "." << std::endl;
	} catch (const std::exception &e) {
		std::cout << getName() << " couldn't sign " << form.getName()
				  << " because " << e.what() << "." << std::endl;
	}
}

void Bureaucrat::executeForm(AForm const &form) const
{
	try {
		form.execute(*this);
		std::cout << getName() << " executed " << form.getName() << std::endl;
	}
	catch (const std::exception &e) {
		std::cout << getName() << " couldn't execute " << form.getName() 
				  << " because " << e.what() << std::endl;
	}
}

std::ostream &operator<<(std::ostream &os, const Bureaucrat &bureaucrat)
{
	os << bureaucrat.getName() << ", bureaucrat grade " << bureaucrat.getGrade();
	return os;
}
