#include "Span.hpp"
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

int main()
{
	// PDFからのテスト
	std::cout << "=== PDFからのテスト ===" << std::endl;
	Span sp = Span(5);
	sp.addNumber(6);
	sp.addNumber(3);
	sp.addNumber(17);
	sp.addNumber(9);
	sp.addNumber(11);
	std::cout << sp.shortestSpan() << std::endl;
	std::cout << sp.longestSpan() << std::endl;

	std::cout << "\n=== Exceptionのテスト ===" << std::endl;
	
	// FullContainerExceptionのテスト
	try
	{
		sp.addNumber(42);
	}
	catch(const std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	// NoSpanExceptionのテスト
	try
	{
		Span empty(10);
		empty.shortestSpan();
	}
	catch(const std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	// NoSpanExceptionのテスト(空のコンテナでlongestSpanを呼び出す)
	try
	{
		Span single(10);
		single.addNumber(42);
		single.longestSpan();
	}
	catch(const std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== Range additionのテスト ===" << std::endl;
	
	// vectorでのrange additionのテスト
	std::vector<int> vec;
	for (int i = 0; i < 1000; ++i)
		vec.push_back(i * 2);

	Span bigSpan(1000);
	try
	{
		bigSpan.addRange(vec.begin(), vec.end());
		std::cout << "Added " << bigSpan.size() << " elements" << std::endl;
		std::cout << "Shortest span: " << bigSpan.shortestSpan() << std::endl;
		std::cout << "Longest span: " << bigSpan.longestSpan() << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== 10000個以上の要素でのテスト ===" << std::endl;
	
	// 10000個以上の要素でのテスト
	Span hugeSpan(15000);
	srand(time(NULL));
	
	// 個別に数値を追加
	for (int i = 0; i < 5000; ++i)
		hugeSpan.addNumber(rand() % 50000);
	
	// 数値の範囲を追加
	std::vector<int> rangeVec;
	for (int i = 0; i < 10000; ++i)
		rangeVec.push_back(rand() % 100000);
	
	try
	{
		hugeSpan.addRange(rangeVec.begin(), rangeVec.end());
		std::cout << "Successfully added " << hugeSpan.size() << " elements" << std::endl;
		std::cout << "Shortest span: " << hugeSpan.shortestSpan() << std::endl;
		std::cout << "Longest span: " << hugeSpan.longestSpan() << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== RangeTooBigExceptionのテスト ===" << std::endl;
	
	// RangeTooBigExceptionのテスト
	try
	{
		Span small(5);
		std::vector<int> bigVec;
		for (int i = 0; i < 10; ++i)
			bigVec.push_back(i);
		small.addRange(bigVec.begin(), bigVec.end());
	}
	catch(const std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	return 0;
}


// additional flag : -pedantic