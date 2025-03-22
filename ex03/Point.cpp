/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 14:26:38 by myokono           #+#    #+#             */
/*   Updated: 2025/03/22 14:27:05 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

Point::Point() : x(0), y(0) {
}

Point::Point(const float xVal, const float yVal) : x(xVal), y(yVal) {
}

Point::Point(const Point& src) : x(src.x), y(src.y) {
}

Point& Point::operator=(const Point& rhs)
{
	if (this != &rhs) {
		const_cast<Fixed&>(this->x) = rhs.x;
		const_cast<Fixed&>(this->y) = rhs.y;
	}
	return *this;
}

Point::~Point() {
}

Fixed Point::getX() const {
	return this->x;
}

Fixed Point::getY() const {
	return this->y;
}