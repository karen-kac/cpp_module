#include "Zombie.hpp"

int main() {
	int numZombies = 5;
	
	std::cout << "Creating a horde of " << numZombies << " zombies..." << std::endl;
	Zombie* horde = zombieHorde(numZombies, "Horde Zombie");
	
	if (!horde)
		return 1;

	std::cout << "\nMaking all zombies announce:" << std::endl;
	for (int i = 0; i < numZombies; i++) {
		horde[i].announce();
	}
	std::cout << "\nDeleting the zombie horde:" << std::endl;
	delete[] horde;
	
	return 0;
}