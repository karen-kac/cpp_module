#include "Zombie.hpp"

int main(void)
{
	std::cout << "Creating a stack zombie:" << std::endl;
	randomChump("Stack Zombie");

	std::cout << "\nCreating a heap zombie:" << std::endl;
	Zombie* heapZombie = newZombie("Heap Zombie");
	heapZombie->announce();

	std::cout << "Deleting the heap zombie:" << std::endl;
	delete heapZombie;
	
	return 0;
}