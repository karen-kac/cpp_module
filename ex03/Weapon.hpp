/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:49:50 by myokono           #+#    #+#             */
/*   Updated: 2025/03/21 17:49:55 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEAPON_HPP
#define WEAPON_HPP

#include <string>

class Weapon {
private:
	std::string type;

public:
	Weapon();
	Weapon(const std::string& type);
	~Weapon();
	
	const std::string& getType() const;
	void setType(const std::string& type);
};

#endif