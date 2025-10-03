#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>

class BitcoinExchange {
private:
	std::map<std::string, double> _rates; // 日付 → レート

public:
	BitcoinExchange();
	BitcoinExchange(const BitcoinExchange& other);
	BitcoinExchange& operator=(const BitcoinExchange& other);
	~BitcoinExchange();

	void loadDatabase(const std::string& filename);
	void processInput(const std::string& filename) const;

private:
	bool isValidDate(const std::string& date) const;
	bool isValidValue(const std::string& valueStr, double& value) const;
	double getRateForDate(const std::string& date) const;
};

#endif
