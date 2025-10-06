#include "RPN.hpp"

RPN::RPN() {}
RPN::RPN(const RPN& other) { (void)other; }
RPN& RPN::operator=(const RPN& other) { (void)other; return *this; }
RPN::~RPN() {}

bool RPN::isOperator(const std::string& token) const {
	return token == "+" || token == "-" || token == "*" || token == "/";
}

int RPN::applyOperation(int a, int b, const std::string& op) const {
	if (op == "+") return a + b;
	if (op == "-") return a - b;
	if (op == "*") return a * b;
	if (op == "/") {
		if (b == 0)
			throw std::runtime_error("Error");
		return a / b;
	}
	throw std::runtime_error("Error");
}

int RPN::evaluate(const std::string& expression) {
	std::stack<int> st;
	std::stringstream ss(expression);
	std::string token;

	while (ss >> token) {
		if (isOperator(token)) {
			if (st.size() < 2)
				throw std::runtime_error("Error");
			int b = st.top();
			st.pop();
			int a = st.top();
			st.pop();
			int result = applyOperation(a, b, token);
			st.push(result);
		} else {
			// 数字トークンのチェック
			if (token.size() != 1 || !isdigit(token[0]))
				throw std::runtime_error("Error");
			int value = token[0] - '0';
			st.push(value);
		}
	}

	if (st.size() != 1)
		throw std::runtime_error("Error");
	return st.top();
}
