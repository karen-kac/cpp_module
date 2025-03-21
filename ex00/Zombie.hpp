/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:12:25 by myokono           #+#    #+#             */
/*   Updated: 2025/03/21 17:14:02 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include <string>
#include <iostream>

class Zombie {
private:
	std::string name;

public:
	Zombie();
	Zombie(std::string name);
	~Zombie();
	
	void announce(void) const;
	void setName(std::string name);
};

Zombie* newZombie(std::string name);
void randomChump(std::string name);

#endif