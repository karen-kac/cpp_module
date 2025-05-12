#include "Brain.hpp"

Brain::Brain() {
	for (int i = 0; i < 100; i++) {
		this->_ideas[i] = "";
	}
	std::cout << "Brain default constructor called" << std::endl;
}

Brain::Brain(const Brain& other) {
	for (int i = 0; i < 100; i++) {
		this->_ideas[i] = other._ideas[i];
	}
	std::cout << "Brain copy constructor called" << std::endl;
}

Brain& Brain::operator=(const Brain& other) {
	if (this != &other) {
		for (int i = 0; i < 100; i++) {
			this->_ideas[i] = other._ideas[i];
		}
	}
	std::cout << "Brain assignment operator called" << std::endl;
	return *this;
}

Brain::~Brain() {
	std::cout << "Brain destructor called" << std::endl;
}

std::string Brain::getIdea(int index) const {
	return this->_ideas[index];
}

void Brain::setIdea(int index, const std::string& idea) {
	this->_ideas[index] = idea;
}