/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 18:45:24 by myokono           #+#    #+#             */
/*   Updated: 2025/03/07 18:46:02 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"
#include <iostream>
#include <string>

void addNewContact(PhoneBook &phoneBook)
{
	Contact contact;
	std::string input;
	
	std::cout << "Enter first name: ";
	std::getline(std::cin, input);
	if (input.empty())
	{
		std::cout << "Field cannot be empty." << std::endl;
		return;
	}
	contact.setFirstName(input);
	
	std::cout << "Enter last name: ";
	std::getline(std::cin, input);
	if (input.empty())
	{
		std::cout << "Field cannot be empty." << std::endl;
		return;
	}
	contact.setLastName(input);
	
	std::cout << "Enter nickname: ";
	std::getline(std::cin, input);
	if (input.empty())
	{
		std::cout << "Field cannot be empty." << std::endl;
		return;
	}
	contact.setNickname(input);
	
	std::cout << "Enter phone number: ";
	std::getline(std::cin, input);
	if (input.empty())
	{
		std::cout << "Field cannot be empty." << std::endl;
		return;
	}
	contact.setPhoneNumber(input);
	
	std::cout << "Enter darkest secret: ";
	std::getline(std::cin, input);
	if (input.empty())
	{
		std::cout << "Field cannot be empty." << std::endl;
		return;
	}
	contact.setDarkestSecret(input);
	
	phoneBook.addContact(contact);
	std::cout << "Contact added successfully." << std::endl;
}

int main()
{
	PhoneBook phoneBook;
	std::string command;
	
	while (true)
	{
		std::cout << "Enter command (ADD, SEARCH, EXIT): ";
		std::getline(std::cin, command);
		
		if (command == "ADD")
			addNewContact(phoneBook);
		else if (command == "SEARCH")
			phoneBook.searchContact();
		else if (command == "EXIT")
			break;
		else
			std::cout << "Invalid command. Please use ADD, SEARCH, or EXIT." << std::endl;
	}
	
	return 0;
}