/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:50:13 by myokono           #+#    #+#             */
/*   Updated: 2025/03/21 17:50:44 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMANA_HPP
#define HUMANA_HPP

#include <string>
#include <iostream>
#include "Weapon.hpp"

class HumanA {
private:
	std::string name;
	Weapon& weapon;

public:
	HumanA(const std::string& name, Weapon& weapon);
	~HumanA();
	
	void attack() const;
};

#endif