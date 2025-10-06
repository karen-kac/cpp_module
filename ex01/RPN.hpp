#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>
#include <sstream>
#include <string>
#include <stdexcept>

class RPN {
private:
	bool isOperator(const std::string& token) const;
	int applyOperation(int a, int b, const std::string& op) const;

public:
	RPN();
	RPN(const RPN& other);
	RPN& operator=(const RPN& other);
	~RPN();

	int evaluate(const std::string& expression);
};

#endif
