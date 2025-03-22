/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 14:24:55 by myokono           #+#    #+#             */
/*   Updated: 2025/03/22 14:27:35 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

static Fixed area(Point const &a, Point const &b, Point const &c)
{
	// Area = 0.5 * |x1(y2 - y3) + x2(y3 - y1) + x3(y1 - y2)|
	Fixed area = ((a.getX() * (b.getY() - c.getY())) +
				  (b.getX() * (c.getY() - a.getY())) +
				  (c.getX() * (a.getY() - b.getY()))) / Fixed(2);
	
	if (area < Fixed(0))
		area = area * Fixed(-1);
	
	return area;
}

bool bsp(Point const a, Point const b, Point const c, Point const point)
{
	Fixed areaABC = area(a, b, c);

	Fixed areaPBC = area(point, b, c);
	Fixed areaPAC = area(a, point, c);
	Fixed areaPAB = area(a, b, point);

	if (areaPBC == Fixed(0) || areaPAC == Fixed(0) || areaPAB == Fixed(0))
		return false;
	
	// Check if the sum of sub-triangle areas equals the original triangle area
	// This accounts for floating-point precision issues by checking for a small difference
	Fixed sumAreas = areaPBC + areaPAC + areaPAB;
	
	// If the sum of areas is equal to the original triangle's area, the point is inside
	return (sumAreas == areaABC);
}