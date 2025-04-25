#include "PhoneBook.hpp"
#include <iostream>

int main() {
	PhoneBook book;
	std::string cmd;

	std::cout << "Welcome to My Awesome PhoneBook!" << std::endl;
	while (true) {
		std::cout << "\nEnter command (ADD | SEARCH | EXIT): ";
		if (!std::getline(std::cin, cmd)) {
			std::cout << "\nEOF detected. Exiting." << std::endl;
			break;
		}
		if (cmd == "ADD")
			book.add();
		else if (cmd == "SEARCH")
			book.search();
		else if (cmd == "EXIT")
			break;
		else if (!cmd.empty())
			std::cout << "Unknown command." << std::endl;
	}
	return 0;
}