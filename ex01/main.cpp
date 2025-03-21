/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:20:56 by myokono           #+#    #+#             */
/*   Updated: 2025/03/21 17:21:27 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main() {
	int numZombies = 5;
	
	std::cout << "Creating a horde of " << numZombies << " zombies..." << std::endl;
	// ゾンビの群れを作成
	Zombie* horde = zombieHorde(numZombies, "Horde Zombie");
	
	if (!horde)
		return 1;

	std::cout << "\nMaking all zombies announce:" << std::endl;
	for (int i = 0; i < numZombies; i++) {
		horde[i].announce();
	}
	
	// ゾンビの群れを解放
	std::cout << "\nDeleting the zombie horde:" << std::endl;
	delete[] horde;
	
	return 0;
}