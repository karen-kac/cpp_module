#include <iostream>
#include <string>
#include "iter.hpp"

// テスト関数
template<typename T>
void printElement(const T& elem) {
	std::cout << elem << " ";
}

template<typename T>
void incrementElement(T& elem) {
	elem++;
}

void printString(const std::string& str) {
	std::cout << "[" << str << "] ";
}

void upperCaseFirst(std::string& str) {
	if (!str.empty() && str[0] >= 'a' && str[0] <= 'z') {
		str[0] = str[0] - 'a' + 'A';
	}
}

int main(void) {
	std::cout << "=== 整数でテスト ===" << std::endl;
	
	// 非const配列でテスト
	int numbers[] = {1, 2, 3, 4, 5};
	size_t numbersSize = sizeof(numbers) / sizeof(numbers[0]);
	
	std::cout << "Original array: ";
	::iter(numbers, numbersSize, printElement<int>);
	std::cout << std::endl;
	
	// 要素を増やす
	::iter(numbers, numbersSize, incrementElement<int>);
	std::cout << "After increment: ";
	::iter(numbers, numbersSize, printElement<int>);
	std::cout << std::endl;
	
	// const配列でテスト
	const int constNumbers[] = {10, 20, 30};
	size_t constSize = sizeof(constNumbers) / sizeof(constNumbers[0]);
	
	std::cout << "Const array: ";
	::iter(constNumbers, constSize, printElement<int>);
	std::cout << std::endl;
	
	std::cout << "\n=== 文字列でテスト ===" << std::endl;
	
	std::string words[] = {"hello", "world", "templates"};
	size_t wordsSize = sizeof(words) / sizeof(words[0]);
	
	std::cout << "元の文字列: ";
	::iter(words, wordsSize, printString);
	std::cout << std::endl;
	
	// 最初の文字を大文字に変換
	::iter(words, wordsSize, upperCaseFirst);
	std::cout << "大文字に変換後: ";
	::iter(words, wordsSize, printString);
	std::cout << std::endl;
	
	// const文字列配列でテスト
	const std::string constWords[] = {"const", "string", "array"};
	size_t constWordsSize = sizeof(constWords) / sizeof(constWords[0]);
	
	std::cout << "const文字列配列: ";
	::iter(constWords, constWordsSize, printString);
	std::cout << std::endl;
	
	return 0;
}