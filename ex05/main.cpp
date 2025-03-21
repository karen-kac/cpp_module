/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:59:53 by myokono           #+#    #+#             */
/*   Updated: 2025/03/21 17:59:59 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

int main() {
	Harl harl;
	
	std::cout << "Testing all complaint levels:" << std::endl;
	std::cout << "----------------------------" << std::endl;
	
	harl.complain("DEBUG");
	harl.complain("INFO");
	harl.complain("WARNING");
	harl.complain("ERROR");
	
	std::cout << "Testing invalid level:" << std::endl;
	std::cout << "--------------------" << std::endl;
	harl.complain("CRITICAL");
	
	return 0;
}
