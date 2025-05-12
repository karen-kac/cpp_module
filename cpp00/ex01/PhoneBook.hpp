#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include "Contact.hpp"
#include <iomanip>

class PhoneBook {
	private:
		Contact _contacts[8];
		int	_count;
		int	_oldest;
	
		static std::string _truncate(const std::string &src);
		static std::string _readField(const std::string &prompt); // ← 追加
		void _printRow(int index, const Contact &c) const;
	public:
		PhoneBook();
		~PhoneBook();
	
		void add();
		void search() const;
	};
	
#endif