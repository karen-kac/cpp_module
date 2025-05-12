#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int main() {
	std::cout << "=== Correct Animal Test ===" << std::endl;
	const Animal* meta = new Animal();
	const Animal* j = new Dog();
	const Animal* i = new Cat();

	std::cout << "Type j: " << j->getType() << std::endl;
	std::cout << "Type i: " << i->getType() << std::endl;

	std::cout << "Sound i (Cat): "; i->makeSound();
	std::cout << "Sound j (Dog): "; j->makeSound();
	std::cout << "Sound meta (Animal): "; meta->makeSound();

	delete meta;
	delete j;
	delete i;

	std::cout << std::endl << "=== Wrong Animal Test ===" << std::endl;
	const WrongAnimal* wrong_meta = new WrongAnimal();
	const WrongAnimal* wrong_cat = new WrongCat();

	std::cout << "Type wrong_cat: " << wrong_cat->getType() << std::endl;

	std::cout << "Sound wrong_cat: "; wrong_cat->makeSound(); // WrongAnimalの音が出てしまう
	std::cout << "Sound wrong_meta: "; wrong_meta->makeSound();

	delete wrong_meta;
	delete wrong_cat;

	return 0;
}

// int main() {
// 	const Animal* meta = new Animal();
// 	const Animal* j = new Dog();
// 	const Animal* i = new Cat();

// 	std::cout << j->getType() << " " << std::endl;
// 	std::cout << i->getType() << " " << std::endl;
// 	i->makeSound();
// 	j->makeSound();
// 	meta->makeSound();

// 	delete meta;
// 	delete j;
// 	delete i;

// 	return 0;
// }
