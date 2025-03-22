/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 14:23:39 by myokono           #+#    #+#             */
/*   Updated: 2025/03/22 14:24:07 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Point.hpp"

int main(void)
{
	Point a(0, 0);
	Point b(10, 30);
	Point c(20, 0);

	Point inside(10, 15);
	Point outside(30, 15);
	Point onVertex(0, 0);
	Point onEdge(10, 0);
	
	std::cout << "Point inside: " << (bsp(a, b, c, inside) ? "Inside" : "Outside") << std::endl;
	std::cout << "Point outside: " << (bsp(a, b, c, outside) ? "Inside" : "Outside") << std::endl;
	std::cout << "Point on vertex: " << (bsp(a, b, c, onVertex) ? "Inside" : "Outside") << std::endl;
	std::cout << "Point on edge: " << (bsp(a, b, c, onEdge) ? "Inside" : "Outside") << std::endl;
	
	return 0;
}