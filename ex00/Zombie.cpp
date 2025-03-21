/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:12:38 by myokono           #+#    #+#             */
/*   Updated: 2025/03/21 17:12:45 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie::Zombie() : name("") {
	std::cout << "Zombie created" << std::endl;
}

Zombie::Zombie(std::string name) : name(name) {
	std::cout << "Zombie " << this->name << " created" << std::endl;
}

Zombie::~Zombie() {
	std::cout << "Zombie " << this->name << " destroyed" << std::endl;
}

void Zombie::announce(void) const {
	std::cout << this->name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}

void Zombie::setName(std::string name) {
	this->name = name;
}
