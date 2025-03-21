/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zombieHorde.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:20:36 by myokono           #+#    #+#             */
/*   Updated: 2025/03/21 17:20:41 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"
#include <sstream> // std::stringstream用

// N個のZombieをヒープ上に作成
Zombie* zombieHorde(int N, std::string name) {
	if (N <= 0) {
		std::cerr << "Error: Number of zombies must be positive" << std::endl;
		return NULL;
	}
	
	// ゾンビの配列を動的に確保
	Zombie* horde = new Zombie[N];
	
	// 各ゾンビに名前を設定
	for (int i = 0; i < N; i++) {
		// C++98では std::to_string が使えないので、文字列変換を手動で行う
		std::stringstream ss;
		ss << name << " #" << (i + 1);
		horde[i].setName(ss.str());
	}
	
	return horde;
}