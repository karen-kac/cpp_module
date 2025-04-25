#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include "Contact.hpp"
#include <iomanip>

class PhoneBook {
private:
    Contact _contacts[8];
    int     _count;      // 登録済み件数 (0〜8)
    int     _oldest;     // 上書き対象インデックス (0〜7)

    static std::string _truncate(const std::string &src);
    void _printRow(int index, const Contact &c) const;
public:
    PhoneBook();
    ~PhoneBook();

    void add();
    void search() const;
};

#endif // PHONEBOOK_HPP