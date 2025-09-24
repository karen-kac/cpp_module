#include "ScalarConverter.hpp"
#include <iostream>
#include <cstdlib>      // atoi, strtod
#include <cctype>       // isprint
#include <climits>      // INT_MAX, INT_MIN
#include <limits>       // numeric_limits
#include <iomanip>      // setprecision
#include <string>

// private メンバの定義（インスタンス化禁止）
ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(const ScalarConverter& other) { (void)other; }
ScalarConverter& ScalarConverter::operator=(const ScalarConverter& other) { (void)other; return *this; }
ScalarConverter::~ScalarConverter() {}

// --- ヘルパー構造体 --- //
struct ScalarValues {
	char cValue;
	int iValue;
	float fValue;
	double dValue;
};

// --- 型判定用enum --- //
enum LiteralType {
	TYPE_CHAR,
	TYPE_INT,
	TYPE_FLOAT,
	TYPE_DOUBLE,
	TYPE_UNKNOWN
};

// --- 型判定関数 --- //
static LiteralType detectType(const std::string &literal) {
	if (literal.length() == 1 && !std::isdigit(literal[0]))
		return TYPE_CHAR;
	if (literal == "nan" || literal == "+inf" || literal == "-inf")
		return TYPE_DOUBLE;
	if (literal == "nanf" || literal == "+inff" || literal == "-inff")
		return TYPE_FLOAT;
	if (literal.find('f') != std::string::npos)
		return TYPE_FLOAT;
	if (literal.find('.') != std::string::npos)
		return TYPE_DOUBLE;
	return TYPE_INT;
}

// --- 値変換関数 --- //
static ScalarValues convertValues(const std::string &literal, LiteralType type) {
	ScalarValues values = {0, 0, 0.0f, 0.0};
	switch (type) {
		case TYPE_CHAR:
			values.cValue = literal[0];
			values.iValue = static_cast<int>(values.cValue);
			values.fValue = static_cast<float>(values.cValue);
			values.dValue = static_cast<double>(values.cValue);
			break;
		case TYPE_INT:
			values.dValue = std::strtod(literal.c_str(), NULL); // まず double で読む
			values.fValue = static_cast<float>(values.dValue);
		
			if (values.dValue > INT_MAX || values.dValue < INT_MIN ||
				values.dValue != values.dValue || // NaN check
				values.dValue == std::numeric_limits<double>::infinity() ||
				values.dValue == -std::numeric_limits<double>::infinity()) {
				values.iValue = 0;  // ダミー
				values.cValue = 0;
			} else {
				values.iValue = static_cast<int>(values.dValue);
				values.cValue = static_cast<char>(values.iValue);
			}
			break;	
		case TYPE_FLOAT:
			values.fValue = static_cast<float>(std::strtod(literal.c_str(), NULL));
			values.iValue = static_cast<int>(values.fValue);
			values.cValue = static_cast<char>(values.iValue);
			values.dValue = static_cast<double>(values.fValue);
			break;
		case TYPE_DOUBLE:
			values.dValue = std::strtod(literal.c_str(), NULL);
			values.iValue = static_cast<int>(values.dValue);
			values.cValue = static_cast<char>(values.iValue);
			values.fValue = static_cast<float>(values.dValue);
			break;
		default:
			break;
	}
	return values;
}

// --- 出力関数 --- //
static void printValues(const ScalarValues &v) {
	double d = v.dValue;
	float  f = v.fValue;
	int    i = v.iValue;
	char   c = v.cValue;

	bool isNan    = (d != d);
	bool isPosInf = (d == std::numeric_limits<double>::infinity());
	bool isNegInf = (d == -std::numeric_limits<double>::infinity());

	// --- char ---
	std::cout << "char: ";
	if (isNan || isPosInf || isNegInf || d > UCHAR_MAX || d < 0)
		std::cout << "impossible" << std::endl;
	else if (std::isprint(c))
		std::cout << "'" << c << "'" << std::endl;
	else
		std::cout << "Non displayable" << std::endl;

	// --- int ---
	std::cout << "int: ";
	if (isNan || isPosInf || isNegInf || d > INT_MAX || d < INT_MIN)
		std::cout << "impossible" << std::endl;
	else
		std::cout << i << std::endl;

	// --- float ---
	std::cout << "float: "
			  << std::fixed << std::setprecision(1) << f << "f" << std::endl;

	// --- double ---
	std::cout << "double: "
			  << std::fixed << std::setprecision(1) << d << std::endl;
}


// --- ScalarConverter本体 --- //
void ScalarConverter::convert(const std::string &literal) {
	LiteralType type = detectType(literal);
	if (type == TYPE_UNKNOWN) {
		std::cerr << "Error: Unknown literal type" << std::endl;
		return;
	}
	ScalarValues values = convertValues(literal, type);
	printValues(values);
}
