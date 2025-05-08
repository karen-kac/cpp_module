#include <iostream>
#include "Fixed.hpp"

int main(void)
{
	Fixed a;
	Fixed b(a); // copy constructor
	Fixed c;
	
	c = b; // copy assignment operator

	std::cout << a.getRawBits() << std::endl;
	std::cout << b.getRawBits() << std::endl;
	std::cout << c.getRawBits() << std::endl;
	
	return 0;
}