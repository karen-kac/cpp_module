#include "DiamondTrap.hpp"

int main(void)
{
	std::cout << "=== Constructing DiamondTrap ===" << std::endl;

	std::cout << "dt1" << std::endl;
	DiamondTrap dt1("Diamondy");
	std::cout << "dt2" << std::endl;
	DiamondTrap dt2(dt1);
	std::cout << "dt3" << std::endl;
	DiamondTrap dt3;
	std::cout << "dt3 = dt1" << std::endl;
	dt3 = dt1;

	std::cout << std::endl;

	std::cout << "=== Basic Function Test ===" << std::endl;
	dt1.attack("TargetBot");
	dt1.takeDamage(40);
	dt1.beRepaired(20);
	dt1.whoAmI();

	std::cout << std::endl;

	std::cout << "=== Parent Class Function Test ===" << std::endl;
	dt1.guardGate();
	dt1.highFivesGuys();

	std::cout << std::endl;

	std::cout << "=== Energy depletion test ===" << std::endl;
	for (int i = 0; i < 10; ++i)
		dt1.attack("DummyTarget");

	std::cout << std::endl;

	std::cout << "=== Destructors will now run ===" << std::endl;
	return 0;
}
