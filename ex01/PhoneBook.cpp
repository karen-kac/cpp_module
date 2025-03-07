/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 18:45:31 by myokono           #+#    #+#             */
/*   Updated: 2025/03/07 18:46:35 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>

PhoneBook::PhoneBook() : oldestIndex(0), count(0) {}

PhoneBook::~PhoneBook() {}

void PhoneBook::addContact(const Contact &contact)
{
	contacts[oldestIndex] = contact;
	oldestIndex = (oldestIndex + 1) % MAX_CONTACTS;
	if (count < MAX_CONTACTS)
		count++;
}

std::string PhoneBook::truncateString(const std::string &str) const
{
	if (str.length() > 10)
		return str.substr(0, 9) + ".";
	return str;
}

void PhoneBook::displayContactHeader() const
{
	std::cout << std::setw(10) << "Index" << "|";
	std::cout << std::setw(10) << "First Name" << "|";
	std::cout << std::setw(10) << "Last Name" << "|";
	std::cout << std::setw(10) << "Nickname" << std::endl;
	std::cout << std::string(43, '-') << std::endl;
}

void PhoneBook::displayContactRow(int index, const Contact &contact) const
{
	std::cout << std::setw(10) << index << "|";
	std::cout << std::setw(10) << truncateString(contact.getFirstName()) << "|";
	std::cout << std::setw(10) << truncateString(contact.getLastName()) << "|";
	std::cout << std::setw(10) << truncateString(contact.getNickname()) << std::endl;
}

bool PhoneBook::isValidIndex(const std::string &input, int &index) const
{
	std::stringstream ss(input);
	
	if (!(ss >> index) || index < 0 || index >= count || !contacts[index].isEmpty())
		return false;
	return true;
}

void PhoneBook::displayContactDetails(int index) const
{
	const Contact &contact = contacts[index];
	
	std::cout << "First Name: " << contact.getFirstName() << std::endl;
	std::cout << "Last Name: " << contact.getLastName() << std::endl;
	std::cout << "Nickname: " << contact.getNickname() << std::endl;
	std::cout << "Phone Number: " << contact.getPhoneNumber() << std::endl;
	std::cout << "Darkest Secret: " << contact.getDarkestSecret() << std::endl;
}

void PhoneBook::searchContact() const
{
	if (count == 0)
	{
		std::cout << "Phonebook is empty." << std::endl;
		return;
	}
	
	displayContactHeader();
	for (int i = 0; i < count; i++)
		displayContactRow(i, contacts[i]);
	
	std::string input;
	int index;
	
	std::cout << "Enter index to display: ";
	std::getline(std::cin, input);
	
	if (isValidIndex(input, index))
		displayContactDetails(index);
	else
		std::cout << "Invalid index." << std::endl;
}