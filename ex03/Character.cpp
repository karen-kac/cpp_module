#include "Character.hpp"
#include <iostream>

Character::Character(std::string const & name) : _name(name) {
	std::cout << "Character constructor called with name: " << name << std::endl;
	for (int i = 0; i < 4; ++i)
		_inventory[i] = NULL;
}

Character::Character(const Character& other) : _name(other._name) {
	std::cout << "Character copy constructor called" << std::endl;
	for (int i = 0; i < 4; ++i) {
		if (other._inventory[i])
			_inventory[i] = other._inventory[i]->clone();
		else
			_inventory[i] = NULL;
	}
}

Character& Character::operator=(const Character& other) {
	std::cout << "Character assignment operator called" << std::endl;
	if (this != &other) {
		_name = other._name;
		for (int i = 0; i < 4; ++i) {
			if (_inventory[i])
				delete _inventory[i];
			if (other._inventory[i])
				_inventory[i] = other._inventory[i]->clone();
			else
				_inventory[i] = NULL;
		}
	}
	return *this;
}


Character::~Character() {
	std::cout << "Character destructor called" << std::endl;
	for (int i = 0; i < 4; ++i)
		delete _inventory[i];
}

std::string const & Character::getName() const {
	std::cout << "Character getName called" << std::endl;
	return _name;
}

void Character::equip(AMateria* m) {
	std::cout << "Character equip called" << std::endl;
	if (!m)
		return;
	for (int i = 0; i < 4; ++i) {
		if (_inventory[i] == NULL) {
			_inventory[i] = m;
			break;
		}
	}
}


void Character::unequip(int idx) {
	if (idx >= 0 && idx < 4 && _inventory[idx])
		_inventory[idx] = NULL;
}


void Character::use(int idx, ICharacter& target) {
	if (idx >= 0 && idx < 4 && _inventory[idx])
		_inventory[idx]->use(target);

}