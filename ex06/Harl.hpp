/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 18:02:31 by myokono           #+#    #+#             */
/*   Updated: 2025/03/21 18:02:42 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HARL_HPP
#define HARL_HPP

#include <string>
#include <iostream>

class Harl
{
private:
	void debug(void);
	void info(void);
	void warning(void);
	void error(void);

	typedef void (Harl::*t_func)(void);
	
	// レベル名とそれに対応する関数ポインタの配列
	static const std::string levels[4];
	static const t_func funcs[4];

public:
	Harl();
	~Harl();
	
	void complain(std::string level);
	int getLevelIndex(std::string level) const;
	void filterComplain(std::string level);
};

#endif
