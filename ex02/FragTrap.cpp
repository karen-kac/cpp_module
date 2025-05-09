#include "FragTrap.hpp"

FragTrap::FragTrap() : ClapTrap("DefaultFrag") {
	_hitPoints = 100;
	_energyPoints = 100;
	_attackDamage = 30;
	std::cout << "FragTrap default constructor called" << std::endl;
}

FragTrap::FragTrap(const std::string& name) : ClapTrap(name) {
	_hitPoints = 100;
	_energyPoints = 100;
	_attackDamage = 30;
	std::cout << "FragTrap " << name << " constructor called" << std::endl;
}

FragTrap::FragTrap(const FragTrap& other) : ClapTrap(other) {
	std::cout << "FragTrap copy constructor called" << std::endl;
}

FragTrap& FragTrap::operator=(const FragTrap& other) {
	std::cout << "FragTrap assignment operator called" << std::endl;
	if (this != &other) {
		ClapTrap::operator=(other); // 親クラスの代入演算子を呼ぶ
	}
	return *this;
}

FragTrap::~FragTrap() {
	std::cout << "FragTrap " << _name <<" destructor called" << std::endl;
}

void FragTrap::attack(const std::string& target) {
	if (_energyPoints <= 0 || _hitPoints <= 0) {
		std::cout << "FragTrap " << _name << " has no energy or hit points" << std::endl;
		return;
	}
	_energyPoints--;
	std::cout << "FragTrap " << _name << " attacks " << target << ", causing " << _attackDamage << " points of damage!" << std::endl;
}

void FragTrap::highFivesGuys(void) {
	std::cout << "FragTrap " << _name << " high fives guys" << std::endl;
}