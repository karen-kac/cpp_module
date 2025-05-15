#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "Brain.hpp"

int main() {
	std::cout << "=== Create Cat A ===" << std::endl;
	Cat catA;

	std::cout << "\n=== Copy-Construct Cat B from A ===" << std::endl;
	Cat catB(catA);

	std::cout << "\n=== Create Cat C and Assign A to C ===" << std::endl;
	Cat catC;
	catC = catA;

	std::cout << "\n=== Set ideas for Cat A ===" << std::endl;
	catA.setIdea(0, "I want to play with a ball");
	std::cout << "Cat A idea 0: " << catA.getIdea(0) << std::endl;
	catA.setIdea(1, "I want to sleep");
	std::cout << "Cat A idea 1: " << catA.getIdea(1) << std::endl;
	catA.setIdea(2, "I want to eat fish");
	std::cout << "Cat A idea 2: " << catA.getIdea(2) << std::endl;
	

	std::cout << "\n=== Create Dog X ===" << std::endl;
	Dog dogX;

	std::cout << "\n=== Copy-Construct Dog Y from X ===" << std::endl;
	Dog dogY(dogX);

	std::cout << "\n=== Create Dog Z and Assign X to Z ===" << std::endl;
	Dog dogZ;
	dogZ = dogX;

	std::cout << "\n=== End of main (Destructors will be called) ===" << std::endl;
	return 0;
}


// int main() {
// 	const Animal* j = new Dog();
// 	const Animal* i = new Cat();

// 	delete j;
// 	delete i;

// 	return 0;
// }
