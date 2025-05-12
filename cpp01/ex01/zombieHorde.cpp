#include "Zombie.hpp"
#include <sstream>

Zombie* zombieHorde(int N, std::string name) {
	if (N <= 0) {
		std::cout << "Error: Number of zombies must be positive" << std::endl;
		return NULL;
	}

	Zombie* horde = new Zombie[N];

	for (int i = 0; i < N; i++) {
		std::stringstream ss;
		ss << name << " #" << (i + 1);
		horde[i].setName(ss.str());
	}
	return horde;
}