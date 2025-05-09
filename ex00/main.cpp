#include "ClapTrap.hpp"

int main() {
	ClapTrap clap("cpp");
	
	std::cout << "\n--- Testing ClapTrap ---" << std::endl;
	clap.attack("Target Dummy");
	clap.takeDamage(3);
	clap.beRepaired(2);
	
	// Test energy depletion
	std::cout << "\n--- Testing Energy Depletion ---" << std::endl;
	for (int i = 0; i < 8; ++i) {
		clap.attack("Energy Dummy");
	}
	clap.attack("Energy Dummy"); // Should show out of energy message
	
	// Test destruction
	std::cout << "\n--- Testing Destruction ---" << std::endl;
	ClapTrap victim("Victim");
	victim.takeDamage(15); // Should destroy the ClapTrap
	victim.attack("Someone"); // Should fail because no hit points
	
	return 0;
}