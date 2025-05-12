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
