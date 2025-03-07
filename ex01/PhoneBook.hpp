/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 18:45:34 by myokono           #+#    #+#             */
/*   Updated: 2025/03/07 18:46:47 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

#include "Contact.hpp"

class PhoneBook
{
private:
	static const int MAX_CONTACTS = 8;
	Contact contacts[MAX_CONTACTS];
	int oldestIndex;
	int count;
	
	std::string truncateString(const std::string &str) const;
	void displayContactHeader() const;
	void displayContactRow(int index, const Contact &contact) const;
	void displayContactDetails(int index) const;
	bool isValidIndex(const std::string &input, int &index) const;

public:
	PhoneBook();
	~PhoneBook();
	
	void addContact(const Contact &contact);
	void searchContact() const;
};

#endif