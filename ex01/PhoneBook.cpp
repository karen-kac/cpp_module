#include "PhoneBook.hpp"
#include <cstdlib>

PhoneBook::PhoneBook() : _count(0), _oldest(0) {}
PhoneBook::~PhoneBook() {}

/* 文字列を 10 文字幅に収める。長い場合は 9 文字 + '.' にする */
std::string PhoneBook::_truncate(const std::string &src) {
    if (src.length() > 10)
        return src.substr(0, 9) + ".";
    return src;
}

void PhoneBook::_printRow(int index, const Contact &c) const {
    std::cout << std::setw(10) << index << "|"
              << std::setw(10) << _truncate(c.getFirstName()) << "|"
              << std::setw(10) << _truncate(c.getLastName())  << "|"
              << std::setw(10) << _truncate(c.getNickName())  << std::endl;
}

/* ユーティリティ: 空入力を防ぐ */
static std::string _readField(const std::string &prompt) {
    std::string input;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, input);
        if (std::cin.eof()) { std::cout << "\nEOF detected. Abort add." << std::endl; return ""; }
        if (!input.empty())
            return input;
        std::cout << "Field cannot be empty. Please re‑enter." << std::endl;
    }
}

void PhoneBook::add() {
    Contact c;
    std::string buf;

    buf = _readField("First name      : "); if (buf.empty()) return; c.setFirstName(buf);
    buf = _readField("Last name       : "); if (buf.empty()) return; c.setLastName(buf);
    buf = _readField("Nickname        : "); if (buf.empty()) return; c.setNickName(buf);
    buf = _readField("Phone number    : "); if (buf.empty()) return; c.setPhoneNumber(buf);
    buf = _readField("Darkest secret  : "); if (buf.empty()) return; c.setDarkestSecret(buf);

    _contacts[_oldest] = c;
    _oldest = (_oldest + 1) % 8;
    if (_count < 8) _count++;

    std::cout << "Contact saved successfully!" << std::endl;
}

void PhoneBook::search() const {
    if (_count == 0) { std::cout << "PhoneBook is empty." << std::endl; return; }

    std::cout << std::setw(10) << "Index" << "|"
              << std::setw(10) << "First Name" << "|"
              << std::setw(10) << "Last Name"  << "|"
              << std::setw(10) << "Nickname"   << std::endl;
    for (int i = 0; i < _count; ++i)
        _printRow(i, _contacts[i]);

    std::cout << "Enter index to display > ";
    std::string line; std::getline(std::cin, line);
    if (std::cin.eof()) { std::cout << std::endl; return; }
    int idx = std::atoi(line.c_str());
    if (idx < 0 || idx >= _count) {
        std::cout << "Invalid index." << std::endl;
        return;
    }
    const Contact &c = _contacts[idx];
    std::cout << "First name     : " << c.getFirstName()    << std::endl;
    std::cout << "Last name      : " << c.getLastName()     << std::endl;
    std::cout << "Nickname       : " << c.getNickName()     << std::endl;
    std::cout << "Phone number   : " << c.getPhoneNumber()  << std::endl;
    std::cout << "Darkest secret : " << c.getDarkestSecret()<< std::endl;
}