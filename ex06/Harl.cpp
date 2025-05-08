#include "Harl.hpp"

Harl::Harl() {
}

Harl::~Harl() {
}

void Harl::_debug(void) {
	std::cout << "[ DEBUG ]" << std::endl;
	std::cout << "I love having extra bacon for my 7XL-double-cheese-triple-pickle-special-ketchup burger." << std::endl;
	std::cout << "I really do!" << std::endl << std::endl;
}

void Harl::_info(void) {
	std::cout << "[ INFO ]" << std::endl;
	std::cout << "I cannot believe adding extra bacon costs more money." << std::endl;
	std::cout << "You didn't put enough bacon in my burger! If you did, I wouldn't be asking for more!" << std::endl << std::endl;
}

void Harl::_warning(void) {
	std::cout << "[ WARNING ]" << std::endl;
	std::cout << "I think I deserve to have some extra bacon for free." << std::endl;
	std::cout << "I've been coming for years whereas you started working here since last month." << std::endl << std::endl;
}

void Harl::_error(void) {
	std::cout << "[ ERROR ]" << std::endl;
	std::cout << "This is unacceptable! I want to speak to the manager now." << std::endl << std::endl;
}


void Harl::complain(std::string level) {
	
	std::string levels[] = {
		"DEBUG",
		"INFO",
		"WARNING",
		"ERROR"
	};
	int i = 0;
	for (i = 0; i < 4; i++) {
		if (level == levels[i]) {
			break;
		}
	}
	switch (i) {
		case 0:
			this->_debug();
			// fall through
		case 1:
			this->_info();
			// fall through
		case 2:
			this->_warning();
			// fall through
		case 3:
			this->_error();
			break;
	
		default:
			std::cout << "[ Invalid complaint level ]" << std::endl;
	}
	
}