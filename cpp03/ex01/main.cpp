#include "ScavTrap.hpp"

int main(void)
{
	ClapTrap	hoge("happy");
	ScavTrap	man1("world");

	std::cout << std::endl;

	hoge.attack("happy");
	hoge.takeDamage(5);
	hoge.beRepaired(5);
	hoge.takeDamage(10);
	hoge.beRepaired(5);

	std::cout << std::endl;

	man1.attack("world");
	man1.guardGate();
	man1.takeDamage(95);
	man1.beRepaired(5);
	man1.takeDamage(10);
	man1.beRepaired(5);

	std::cout << std::endl;

	return (0);
}