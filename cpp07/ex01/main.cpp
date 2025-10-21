#include <iostream>
#include <string>
#include "iter.hpp"

//　出力をする関数
template<typename T>
void printElement(const T& elem) {
	std::cout << elem << " ";
}

// 要素を増やす関数
template<typename T>
void incrementElement(T& elem) {
	elem++;
}

// 文字列を出力する関数
void printString(const std::string& str) {
	std::cout << "[" << str << "] ";
}

// 文字列の最初の文字を大文字に変換する関数
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
	
	std::cout << "元の配列: ";
	::iter(numbers, numbersSize, printElement<int>);
	std::cout << std::endl;
	
	// 要素を増やす
	::iter(numbers, numbersSize, incrementElement<int>);
	std::cout << "要素を増やした後: ";
	::iter(numbers, numbersSize, printElement<int>);
	std::cout << std::endl;
	
	// const配列でテスト
	const int constNumbers[] = {10, 20, 30};
	size_t constSize = sizeof(constNumbers) / sizeof(constNumbers[0]);
	
	std::cout << "const配列: ";
	::iter(constNumbers, constSize, printElement<int>);
	std::cout << std::endl;
	
	std::cout << "\n=== 文字列配列でテスト ===" << std::endl;
	
	std::string words[] = {"hello", "world", "templates"};
	size_t wordsSize = sizeof(words) / sizeof(words[0]);
	
	std::cout << "元の文字列配列: ";
	::iter(words, wordsSize, printString);
	std::cout << std::endl;
	
	// 最初の文字を大文字に変換
	::iter(words, wordsSize, upperCaseFirst);
	std::cout << "最初の文字を大文字に変換した後: ";
	::iter(words, wordsSize, printString);
	std::cout << std::endl;
	
	// const文字列配列でテスト
	const std::string constWords[] = {"const", "string", "array"};
	size_t constWordsSize = sizeof(constWords) / sizeof(constWords[0]);
	
	std::cout << "const配列: ";
	::iter(constWords, constWordsSize, printString);
	std::cout << std::endl;
	
	return 0;
}