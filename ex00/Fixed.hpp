/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 14:10:07 by myokono           #+#    #+#             */
/*   Updated: 2025/03/22 14:11:32 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
#define FIXED_HPP

class Fixed
{
private:
	int _fixedPointValue;
	static const int _fractionalBits = 8;

public:
	Fixed();
	Fixed(const Fixed& src);
	Fixed& operator=(const Fixed& rhs);
	~Fixed();

	int getRawBits(void) const;
	void setRawBits(int const raw);
};

#endif