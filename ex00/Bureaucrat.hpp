#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <string>
#include <iostream>
#include <stdexcept>

class Bureaucrat
{
	private:
		const std::string _name;
		int _grade;

	public:
	// 例外クラス
	// std::exceptionを継承して、what()をオーバーライドする
		class GradeTooHighException : public std::exception {
			public:
				const char* what() const throw() {
					return "Grade too high"; 
				}
		};
		class GradeTooLowException : public std::exception {
			public:
				const char* what() const throw() {
					return "Grade too low"; 
				}
		};

		// コンストラクタ、コピーコンストラクタ、代入演算子、デストラクタ
		// コンストラクタはクラスオブジェクトを生成して初期化する
		Bureaucrat();
		Bureaucrat(const std::string &name, int grade);
		Bureaucrat(const Bureaucrat &other);
		Bureaucrat &operator=(const Bureaucrat &other);
		~Bureaucrat();

		// ゲッター
		// 変更不可なメンバ変数のため、ゲッターを使用して取得する
		const std::string &getName() const;
		int getGrade() const;

		// メンバ関数
		void incrementGrade();
		void decrementGrade();
};

// 演算子オーバーロード
std::ostream &operator<<(std::ostream &os, const Bureaucrat &bureaucrat);

#endif
