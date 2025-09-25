#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>



Base* generate(void) {
	// Initialize random seed once
	static bool seeded = false;
	if (!seeded) {
		std::srand(static_cast<unsigned int>(std::time(0)));
		seeded = true;
	}

	int random = std::rand() % 3;
	switch (random) {
		case 0:
			std::cout << "Generated: A" << std::endl;
			return new A();
		case 1:
			std::cout << "Generated: B" << std::endl;
			return new B();
		default:
			std::cout << "Generated: C" << std::endl;
			return new C();
	}
}

// Prints the actual type of the object pointed to by p
void identify(Base* p) {
	if (dynamic_cast<A*>(p)) {
		std::cout << "A" << std::endl;
	} else if (dynamic_cast<B*>(p)) {
		std::cout << "B" << std::endl;
	} else if (dynamic_cast<C*>(p)) {
		std::cout << "C" << std::endl;
	} else {
		std::cout << "Unknown type" << std::endl;
	}
}

// Prints the actual type of the object referenced by p
// Using a pointer inside this function is forbidden
void identify(Base& p) {
	try {
		dynamic_cast<A&>(p);
		std::cout << "A" << std::endl;
		return;
	} catch (const std::bad_cast&) {
		// Not type A, continue checking
	}

	try {
		dynamic_cast<B&>(p);
		std::cout << "B" << std::endl;
		return;
	} catch (const std::bad_cast&) {
		// Not type B, continue checking
	}

	try {
		dynamic_cast<C&>(p);
		std::cout << "C" << std::endl;
		return;
	} catch (const std::bad_cast&) {
		// Not type C
	}

	std::cout << "Unknown type" << std::endl;
}

int main() {
	std::cout << "=== Exercise 02: Identify real type ===" << std::endl;

	// Test multiple times to see random generation
	for (int i = 0; i < 5; ++i) {
		std::cout << "\n--- Test " << (i + 1) << " ---" << std::endl;
		
		// Generate random object
		Base* obj = generate();
		
		// Test identify with pointer
		std::cout << "identify(Base* p): ";
		identify(obj);
		
		// Test identify with reference
		std::cout << "identify(Base& p): ";
		identify(*obj);
		
		// Clean up memory
		delete obj;
	}

	std::cout << "\n=== Additional Tests ===" << std::endl;
	
	// Test each type explicitly
	std::cout << "\nExplicit A test:" << std::endl;
	Base* a = new A();
	std::cout << "identify(A* as Base*): ";
	identify(a);
	std::cout << "identify(A& as Base&): ";
	identify(*a);
	delete a;

	std::cout << "\nExplicit B test:" << std::endl;
	Base* b = new B();
	std::cout << "identify(B* as Base*): ";
	identify(b);
	std::cout << "identify(B& as Base&): ";
	identify(*b);
	delete b;

	std::cout << "\nExplicit C test:" << std::endl;
	Base* c = new C();
	std::cout << "identify(C* as Base*): ";
	identify(c);
	std::cout << "identify(C& as Base&): ";
	identify(*c);
	delete c;

	return 0;
}