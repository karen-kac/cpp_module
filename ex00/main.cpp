#include "ScalarConverter.hpp"
#include <iostream>

int main(int argc, char **argv) {
	if (argc != 2) {
		std::cerr << "Usage: " << argv[0] << " <literal>" << std::endl;
		return 1;
	}

	ScalarConverter::convert(argv[1]);
	return 0;
}


// // テスター用
// #include "ScalarConverter.hpp"
// #include <iostream>
// #include <vector>
// #include <string>

// int main() {
// 	std::vector<std::string> tests;

// 	// --- 基本整数 ---
// 	tests.push_back("0");
// 	tests.push_back("42");
// 	tests.push_back("-42");
// 	tests.push_back("2147483647");  // INT_MAX
// 	tests.push_back("2147483648");  // INT_MAX+1 → overflow

// 	// --- char ---
// 	tests.push_back("'A'");
// 	tests.push_back("' '");
// 	tests.push_back("'~'");
// 	tests.push_back("31");   // 制御文字
// 	tests.push_back("32");   // スペース
// 	tests.push_back("126");  // '~'
// 	tests.push_back("127");  // DEL

// 	// --- 浮動小数 ---
// 	tests.push_back("42.0f");
// 	tests.push_back("42.0");
// 	tests.push_back("-42.5");
// 	tests.push_back("4.2f");
// 	tests.push_back("-4.2f");
// 	tests.push_back("4.2F");   // 大文字F
// 	tests.push_back("-4.2F");  // 大文字F
// 	tests.push_back("3.4e38f");   // float max付近
// 	tests.push_back("3.5e38f");   // float overflow

// 	// --- double ---
// 	tests.push_back("1.7e308");   // double max付近
// 	tests.push_back("1.9e308");   // double overflow
// 	tests.push_back("-1.9e308");  // double overflow(負)

// 	// --- 特殊値 ---
// 	tests.push_back("nan");
// 	tests.push_back("nanf");
// 	tests.push_back("+inf");
// 	tests.push_back("+inff");
// 	tests.push_back("-inf");
// 	tests.push_back("-inff");

// 	// --- 無効入力 ---
// 	tests.push_back("hello");
// 	tests.push_back("123abc");
// 	tests.push_back("<hkgs,2>");
// 	tests.push_back("''");
// 	tests.push_back("");   // 空文字

// 	// 実行
// 	for (size_t k = 0; k < tests.size(); ++k) {
// 		std::cout << "==== Test " << k+1 << ": \"" << tests[k] << "\" ====" << std::endl;
// 		ScalarConverter::convert(tests[k]);
// 		std::cout << std::endl;
// 	}

// 	return 0;
// }




/*expected.txt
==== Test 1: "0" ====
char: Non displayable
int: 0
float: 0.0f
double: 0.0

==== Test 2: "42" ====
char: '*'
int: 42
float: 42.0f
double: 42.0

==== Test 3: "-42" ====
char: impossible
int: -42
float: -42.0f
double: -42.0

==== Test 4: "2147483647" ====
char: impossible
int: 2147483647
float: 2147483648.0f
double: 2147483647.0

==== Test 5: "2147483648" ====
char: impossible
int: impossible
float: 2147483648.0f
double: 2147483648.0

==== Test 6: "'A'" ====
char: 'A'
int: 65
float: 65.0f
double: 65.0

==== Test 7: "' '" ====
char: ' '
int: 32
float: 32.0f
double: 32.0

==== Test 8: "'~'" ====
char: '~'
int: 126
float: 126.0f
double: 126.0

==== Test 9: "127" ====
char: Non displayable
int: 127
float: 127.0f
double: 127.0

==== Test 10: "42.0f" ====
char: '*'
int: 42
float: 42.0f
double: 42.0

==== Test 11: "42.0" ====
char: '*'
int: 42
float: 42.0f
double: 42.0

==== Test 12: "-42.5" ====
char: impossible
int: -42
float: -42.5f
double: -42.5

==== Test 13: "3.4e38f" ====
char: impossible
int: impossible
float: 339999995214436424907732413799364296704.0f
double: 339999999999999996123846586046231871488.0

==== Test 14: "3.5e38f" ====
char: impossible
int: impossible
float: inff
double: 350000000000000001565567347835409530880.0

==== Test 15: "1.7e308" ====
char: impossible
int: impossible
float: inff
double: 169999999999999993883079578865998174333346074304075874502773119193537729178160565864330091787584707988572262467983188919169916105593357174268369962062473635296474636515660464935663040684957844303524367815028553272712298986386310828644513212353921123253311675499856875650512437415429217994623324794855339589632.0

==== Test 16: "1.9e308" ====
char: impossible
int: impossible
float: inff
double: inf

==== Test 17: "-1.9e308" ====
char: impossible
int: impossible
float: -inff
double: -inf

==== Test 18: "nan" ====
char: impossible
int: impossible
float: nanf
double: nan

==== Test 19: "nanf" ====
char: impossible
int: impossible
float: nanf
double: nan

==== Test 20: "+inf" ====
char: impossible
int: impossible
float: inff
double: inf

==== Test 21: "+inff" ====
char: impossible
int: impossible
float: inff
double: inf

==== Test 22: "-inf" ====
char: impossible
int: impossible
float: -inff
double: -inf

==== Test 23: "-inff" ====
char: impossible
int: impossible
float: -inff
double: -inf

==== Test 24: "hello" ====
char: impossible
int: impossible
float: impossible
double: impossible

==== Test 25: "123abc" ====
char: impossible
int: impossible
float: impossible
double: impossible

==== Test 26: "<hkgs,2>" ====
char: impossible
int: impossible
float: impossible
double: impossible

==== Test 27: "''" ====
char: impossible
int: impossible
float: impossible
double: impossible
*/


/*
test.sh

① main.cppをテスト用に変更
② expected.txtを生成
③ test.shを実行


#!/bin/bash

# コンパイル
make re

# 実行結果保存
./ScalarConverter > output.txt

# 期待される出力ファイルがある場合は比較
if [ -f expected.txt ]; then
	echo "🔍 Comparing with expected.txt..."
	diff -u expected.txt output.txt
	if [ $? -eq 0 ]; then
		echo "✅ All tests passed!"
	else
		echo "❌ Differences found!"
	fi
else
	echo "⚠️ expected.txt が見つかりません。"
	echo "   output.txt を expected.txt として保存してください:"
	echo "   cp output.txt expected.txt"
fi
*/