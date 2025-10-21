#ifndef AFORM_HPP
#define AFORM_HPP

#include <string>
#include <iostream>
#include <stdexcept>

class Bureaucrat;

class AForm
{
	private:
		const std::string _name;
		bool _isSigned;
		const int _gradeToSign;
		const int _gradeToExecute;

	// 純粋仮想関数
	// テンプレートメソッドパターン（この部分だけ派生クラスで実装する）
	protected:
		virtual void executeAction() const = 0;
	
	// 公開メンバ関数
	public:
		class GradeTooHighException : public std::exception {
			public:
				virtual const char* what() const throw();
		};
		class GradeTooLowException : public std::exception {
			public:
				virtual const char* what() const throw(); 
		};
		class AlreadySignedException : public std::exception {
			public:
			const char* what() const throw();
		};
		class FormNotSignedException : public std::exception {
			public:
				virtual const char* what() const throw();
		};

		AForm();
		AForm(const std::string &name, int gradeToSign, int gradeToExecute);
		AForm(const AForm &other);
		AForm &operator=(const AForm &other);
		// デストラクタは純粋仮想関数virtualはメモリ管理のため、=0は抽象クラスを表す
		virtual ~AForm() = 0;

		const std::string &getName() const;
		bool getIsSigned() const;
		int getGradeToSign() const;
		int getGradeToExecute() const;
		void beSigned(const Bureaucrat &bureaucrat);
		virtual void execute(const Bureaucrat &executor) const;
};

std::ostream &operator<<(std::ostream &os, const AForm &form);

#endif
