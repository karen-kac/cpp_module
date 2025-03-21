/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:51:09 by myokono           #+#    #+#             */
/*   Updated: 2025/03/21 17:51:13 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMANB_HPP
#define HUMANB_HPP

#include <string>
#include <iostream>
#include "Weapon.hpp"

class HumanB {
private:
	std::string name;
	Weapon* weapon; // ポインタを使用（武器を持たない可能性あり）

public:
	HumanB(const std::string& name);
	~HumanB();
	
	void setWeapon(Weapon& weapon);
	void attack() const;
};

#endif