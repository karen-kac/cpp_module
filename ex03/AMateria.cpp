#include "AMateria.hpp"
#include <iostream>

AMateria::AMateria() : _type("AMateria") {
	std::cout << "AMateria default constructor called" << std::endl;
}

AMateria::AMateria(std::string const & type) : _type(type) {
	std::cout << "AMateria constructor called with type: " << type << std::endl;
}

AMateria::AMateria(const AMateria& other) : _type(other._type) {
	std::cout << "AMateria copy constructor called" << std::endl;
}

AMateria& AMateria::operator=(const AMateria& other) {
	std::cout << "AMateria assignment operator called" << std::endl;
	if (this != &other) {
		_type = other._type;
	}
	return *this;
}

AMateria::~AMateria() {
	std::cout << "AMateria destructor called" << std::endl;
}

std::string const & AMateria::getType() const {
	std::cout << "AMateria getType called" << std::endl;
	return this->_type;
}

void AMateria::use(ICharacter& target) {
	std::cout << "AMateria use called" << std::endl;
	(void)target;
}
