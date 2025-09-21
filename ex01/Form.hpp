#ifndef FORM_HPP
#define FORM_HPP

#include <string>
#include <iostream>
#include <stdexcept>

class Bureaucrat;

class Form
{
	private:
		const std::string _name;
		bool _isSigned;
		const int _gradeToSign;
		const int _gradeToExecute;

	public:
		class GradeTooHighException : public std::exception {
			public:
				const char* what() const throw()
				{ 
					return "Grade too high";
				}
		};
		class GradeTooLowException : public std::exception {
			public:
				const char* what() const throw()
				{ 
					return "Grade too low"; 
				}
		};
		class AlreadySignedException : public std::exception {
			public:
			const char* what() const throw()
			{
				return "Form::Already signed";
			}
		};
		Form();
		Form(const std::string &name, int gradeToSign, int gradeToExecute);
		Form(const Form &other);
		Form &operator=(const Form &other);
		~Form();

		const std::string &getName() const;
		bool getIsSigned() const;
		int getGradeToSign() const;
		int getGradeToExecute() const;
		void beSigned(const Bureaucrat &bureaucrat);
};

std::ostream &operator<<(std::ostream &os, const Form &form);

#endif
