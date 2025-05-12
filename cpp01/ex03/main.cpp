#include "Weapon.hpp"
#include "HumanA.hpp"
#include "HumanB.hpp"

int main()
{
	{
		Weapon club = Weapon("crude spiked club");

		HumanA bob("Bob", club);
		bob.attack();
		club.setType("some other type of club");
		bob.attack();
	}
	{
		Weapon club = Weapon("crude spiked club");

		HumanB jim("Jim");
		jim.setWeapon(club);
		jim.attack();
		club.setType("some other type of club");
		jim.attack();
	}
	return 0;
}

// int main() {
// 	{
// 		std::cout << "== HumanA test ==" << std::endl;
// 		Weapon club("crude spiked club");
// 		HumanA bob("Bob", club);
// 		bob.attack();
// 		club.setType("some other type of club");
// 		bob.attack();
// 	}

// 	std::cout << std::endl;

// 	{
// 		std::cout << "== HumanB test ==" << std::endl;
// 		Weapon club("crude spiked club");
// 		HumanB jim("Jim");
// 		jim.attack(); // no weapon
// 		jim.setWeapon(club);
// 		jim.attack();
// 		club.setType("some other type of club");
// 		jim.attack();
// 	}

// 	return 0;
// }
