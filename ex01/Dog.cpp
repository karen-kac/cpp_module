#include "Dog.hpp"

Dog::Dog() : Animal(){
	this->type = "Dog";
	this->_brain = new Brain();
	std::cout << "Dog default constructor called" << std::endl;
}

Dog::Dog(const Dog& other) : Animal(other) {
	this->_brain = new Brain(*other._brain);
	std::cout << "Dog copy constructor called" << std::endl;
}

Dog& Dog::operator=(const Dog& other) {
	if (this != &other) {
		type = other.type;
		if (this->_brain)
			delete this->_brain;
		this->_brain = new Brain(*other._brain);
	}
	std::cout << "Dog assignment operator called" << std::endl;
	return *this;
}

Dog::~Dog() {
	delete this->_brain;
	std::cout << "Dog destructor called" << std::endl;
}

void Dog::makeSound() const {
	std::cout << "Woof!" << std::endl;
}
