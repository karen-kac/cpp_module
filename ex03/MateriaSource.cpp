#include "MateriaSource.hpp"
#include <iostream>

MateriaSource::MateriaSource() {
	std::cout << "MateriaSource constructor called" << std::endl;
	for (int i = 0; i < 4; ++i)
		_materias[i] = NULL;
}

MateriaSource::MateriaSource(const MateriaSource& other) {
	std::cout << "MateriaSource copy constructor called" << std::endl;
	for (int i = 0; i < 4; ++i) {
		if (other._materias[i])
			_materias[i] = other._materias[i]->clone();
		else
			_materias[i] = NULL;
	}
}


MateriaSource& MateriaSource::operator=(const MateriaSource& other) {
	std::cout << "MateriaSource assignment operator called" << std::endl;
	if (this != &other) {
		for (int i = 0; i < 4; ++i){
			if (_materias[i])
				delete _materias[i];
			if (other._materias[i])
				_materias[i] = other._materias[i]->clone();
			else
				_materias[i] = NULL;
		}
	}
	return *this;
}

MateriaSource::~MateriaSource() {
	std::cout << "MateriaSource destructor called" << std::endl;
	for (int i = 0; i < 4; ++i)
		delete _materias[i];
}

void MateriaSource::learnMateria(AMateria* m) {
	std::cout << "MateriaSource learnMateria called" << std::endl;
	if (!m)
		return;
	for (int i = 0; i < 4; ++i) {
		if (_materias[i] == NULL) {
			_materias[i] = m;
			break;
		}
	}
}


AMateria* MateriaSource::createMateria(std::string const & type) {
	std::cout << "MateriaSource createMateria called" << std::endl;
	for (int i = 0; i < 4; ++i) {
		if (_materias[i] && _materias[i]->getType() == type)
			return _materias[i]->clone();
	}
	return NULL;
}
