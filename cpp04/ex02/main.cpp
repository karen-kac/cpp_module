#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "Brain.hpp"

int main() {
	std::cout << "=== Create Dog and Cat via Animal* ===" << std::endl;
	// const Animal* meta = new Animal(); // This will cause a compilation error
	const Animal* dog = new Dog();
	const Animal* cat = new Cat();

	std::cout << "\n=== Check Types ===" << std::endl;
	std::cout << "Dog type: " << dog->getType() << std::endl;
	std::cout << "Cat type: " << cat->getType() << std::endl;

	std::cout << "\n=== Make Sounds ===" << std::endl;
	dog->makeSound(); // Woof!
	cat->makeSound(); // Meow

	std::cout << "\n=== Delete Objects ===" << std::endl;
	delete dog;
	delete cat;

	return 0;
}
