#include "Harl.hpp"

int main() {
	Harl harl;
	
	std::cout << "Testing all complaint levels:" << std::endl;
	std::cout << "----------------------------" << std::endl;
	
	harl.complain("DEBUG");
	harl.complain("INFO");
	harl.complain("WARNING");
	harl.complain("ERROR");
	
	std::cout << "Testing invalid level:" << std::endl;
	std::cout << "--------------------" << std::endl;
	harl.complain("CRITICAL");
	
	return 0;
}
