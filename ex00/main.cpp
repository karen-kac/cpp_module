/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:13:21 by myokono           #+#    #+#             */
/*   Updated: 2025/03/21 17:14:31 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main() {
	std::cout << "Creating a stack zombie:" << std::endl;
	randomChump("Stack Zombie");

	std::cout << "\nCreating a heap zombie:" << std::endl;
	Zombie* heapZombie = newZombie("Heap Zombie");
	heapZombie->announce();

	std::cout << "\nDeleting the heap zombie:" << std::endl;
	delete heapZombie;
	
	return 0;
}