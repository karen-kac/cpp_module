#include "DiamondTrap.hpp"

DiamondTrap::DiamondTrap() : ClapTrap("DefaultDiamond"), ScavTrap(), FragTrap() {
	_name = "DefaultDiamond";
	std::cout << "DiamondTrap default constructor called" << std::endl;
}

DiamondTrap::DiamondTrap(const std::string& name) : ClapTrap(name + "_clap_name"), ScavTrap(name), FragTrap(name) {
	_name = name;
	std::cout << "DiamondTrap " << name << " constructor called" << std::endl;
}

DiamondTrap::DiamondTrap(const DiamondTrap& other) : ClapTrap(other), ScavTrap(other), FragTrap(other) {
	_name = other._name;
	std::cout << "DiamondTrap copy constructor called" << std::endl;
}

DiamondTrap& DiamondTrap::operator=(const DiamondTrap& other) {
	std::cout << "DiamondTrap assignment operator called" << std::endl;
	if (this != &other) {
		ClapTrap::operator=(other);
		this->_name = other._name;
	}
	return *this;
}

DiamondTrap::~DiamondTrap() {
	std::cout << "DiamondTrap " << this->_name << " destructor called" << std::endl;
}

void DiamondTrap::attack(const std::string& target) {
	ScavTrap::attack(target);
}

void DiamondTrap::whoAmI(void) {
	std::cout << "DiamondTrap name: " << this->_name << ", ClapTrap name: " << this->ClapTrap::_name << std::endl;
}