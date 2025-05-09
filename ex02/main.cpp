#include "FragTrap.hpp"

int main(void)
{
	std::cout << "=== Constructing FragTrap ===" << std::endl;

	FragTrap ft1("Pikachu");
	FragTrap ft2(ft1);
	FragTrap ft3;

	std::cout << std::endl;

	ft3 = ft1;

	std::cout << std::endl;

	ft1.attack("Eevee");
	ft1.takeDamage(50);
	ft1.beRepaired(30);
	ft1.highFivesGuys();

	std::cout << std::endl;

	ft2.attack("Charmander");
	ft2.takeDamage(120);
	ft2.beRepaired(20);

	std::cout << std::endl;

	std::cout << "=== Destructors will be called automatically ===" << std::endl;
	return 0;
}
