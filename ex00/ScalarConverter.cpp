#include "ScalarConverter.hpp"
#include <iostream>
#include <cstdlib>
#include <cctype>
#include <climits>
#include <limits>
#include <iomanip>
#include <string>

static bool isChar(const std::string& str) {
	if (str.length() == 3 && str[0] == '\'' && str[2] == '\'')
		return true;
	if (str.length() == 1 && !std::isdigit(str[0]))
		return true;
	return false;
}

static bool isFloatPseudo(const std::string& str) {
	// 小文字と大文字両方に対応
	return str == "-inff" || str == "+inff" || str == "nanf" ||
	       str == "-infF" || str == "+infF" || str == "nanF";
}

static bool isDoublePseudo(const std::string& str) {
	return str == "-inf" || str == "+inf" || str == "nan";
}

void ScalarConverter::convert(const std::string& literal)
{
	char    c = 0;
	int     i = 0;
	float   f = 0.0f;
	double  d = 0.0;

	try {
		if (isChar(literal)) {
			if (literal.length() == 1) {
				c = literal[0];
			} else {
				c = literal[1];
			}
			i = static_cast<int>(c);
			f = static_cast<float>(c);
			d = static_cast<double>(c);
		}
		else if (isFloatPseudo(literal)) {
			f = static_cast<float>(std::strtod(literal.c_str(), NULL));
			d = static_cast<double>(f);
			i = 0;
			c = 0;
		} 
		else if (isDoublePseudo(literal)) {
			d = std::strtod(literal.c_str(), NULL);
			f = static_cast<float>(d);
			i = 0;
			c = 0;
		} 
		else {
			// --- 空文字列チェック ---
			if (literal.empty()) {
				std::cout << "char: impossible" << std::endl;
				std::cout << "int: impossible" << std::endl;
				std::cout << "float: impossible" << std::endl;
				std::cout << "double: impossible" << std::endl;
				return;
			}
			
			// --- strtodで安全に数値変換 ---
			char *end;
			d = std::strtod(literal.c_str(), &end);
			
			// 何も変換されなかった場合（end が開始位置と同じ）もチェック
			if (end == literal.c_str() || (*end != '\0' && !((*end == 'f' || *end == 'F') && *(end+1) == '\0'))) {
				// 変換不可能
				std::cout << "char: impossible" << std::endl;
				std::cout << "int: impossible" << std::endl;
				std::cout << "float: impossible" << std::endl;
				std::cout << "double: impossible" << std::endl;
				return;
			}
			f = static_cast<float>(d);
			i = static_cast<int>(d);
			c = static_cast<char>(i);
		}

		// --- 出力処理 ---

		// char
		std::cout << "char: ";
		if (d != d || d == std::numeric_limits<double>::infinity()
			|| d == -std::numeric_limits<double>::infinity()
			|| d > UCHAR_MAX || d < 0)
			std::cout << "impossible" << std::endl;
		else if (std::isprint(c))
			std::cout << "'" << c << "'" << std::endl;
		else
			std::cout << "Non displayable" << std::endl;

		// int
		std::cout << "int: ";
		if (d != d || d == std::numeric_limits<double>::infinity()
			|| d == -std::numeric_limits<double>::infinity()
			|| d > INT_MAX || d < INT_MIN)
			std::cout << "impossible" << std::endl;
		else
			std::cout << i << std::endl;

		// float
		std::cout << "float: " << std::fixed << std::setprecision(1) << f << "f" << std::endl;

		// double
		std::cout << "double: " << std::fixed << std::setprecision(1) << d << std::endl;
	}
	catch(...) {
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: impossible" << std::endl;
		std::cout << "double: impossible" << std::endl;
	}
}
