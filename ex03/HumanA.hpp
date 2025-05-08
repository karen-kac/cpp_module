#ifndef HUMANA_HPP
#define HUMANA_HPP

#include <string>
#include <iostream>
#include "Weapon.hpp"

class HumanA {
private:
	std::string _name;
	const Weapon& _weapon;

public:
	HumanA(const std::string& name, const Weapon& weapon);
	~HumanA();
	
	void attack() const;
};

#endif