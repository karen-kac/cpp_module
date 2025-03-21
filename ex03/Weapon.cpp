/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:50:00 by myokono           #+#    #+#             */
/*   Updated: 2025/03/21 17:50:04 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"

Weapon::Weapon() : type("") {
}

Weapon::Weapon(const std::string& type) : type(type) {
}

Weapon::~Weapon() {
}

const std::string& Weapon::getType() const {
	return this->type;
}

void Weapon::setType(const std::string& type) {
	this->type = type;
}