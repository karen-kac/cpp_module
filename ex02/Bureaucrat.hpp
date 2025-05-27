#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <string>
#include <iostream>
#include <stdexcept>

class AForm;

class Bureaucrat
{
	private:
		const std::string _name;
		int _grade;

	public:
		class GradeTooHighException : public std::exception {
			public:
				virtual const char* what() const throw() { return "Grade too high"; }
		};
		class GradeTooLowException : public std::exception {
			public:
				virtual const char* what() const throw() { return "Grade too low"; }
		};

		Bureaucrat();
		Bureaucrat(const std::string &name, int grade);
		Bureaucrat(const Bureaucrat &other);
		Bureaucrat &operator=(const Bureaucrat &other);
		~Bureaucrat();

		const std::string &getName() const;
		int getGrade() const;

		void incrementGrade();
		void decrementGrade();

		void signForm(AForm &form);
		void executeForm(const AForm &form) const;
};

std::ostream &operator<<(std::ostream &os, const Bureaucrat &bureaucrat);

#endif
