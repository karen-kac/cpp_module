#include "Cat.hpp"

Cat::Cat() : Animal(){
	this->type = "Cat";
	this->_brain = new Brain();
	std::cout << "Cat default constructor called" << std::endl;
}

Cat::Cat(const Cat& other) : Animal(other) {
	this->_brain = new Brain(*other._brain);
	std::cout << "Cat copy constructor called" << std::endl;
}

Cat& Cat::operator=(const Cat& other) {
	if (this != &other) {
		type = other.type;
		if (this->_brain)
			delete this->_brain;
		this->_brain = new Brain(*other._brain);
	}
	std::cout << "Cat assignment operator called" << std::endl;
	return *this;
}


Cat::~Cat() {
	delete this->_brain;
	std::cout << "Cat destructor called" << std::endl;
}

void Cat::makeSound() const {
	std::cout << "Meow" << std::endl;
}

std::string Cat::getIdea(int index) const {
	return this->_brain->getIdea(index);
}

void Cat::setIdea(int index, const std::string& idea) {
	this->_brain->setIdea(index, idea);
}	
