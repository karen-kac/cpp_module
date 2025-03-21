/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 18:03:54 by myokono           #+#    #+#             */
/*   Updated: 2025/03/21 18:03:59 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
	if (argc != 2) {
		std::cout << "Usage: " << argv[0] << " [DEBUG|INFO|WARNING|ERROR]" << std::endl;
		return 1;
	}
	
	Harl harl;
	std::string level = argv[1];
	
	std::cout << "Filtering for complaints of level " << level << " and above:" << std::endl;
	std::cout << "----------------------------------------------" << std::endl;
	
	harl.filterComplain(level);
	
	return 0;
}
