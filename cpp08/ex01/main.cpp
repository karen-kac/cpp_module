#include "Span.hpp"
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <list>
#include <deque>

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

	std::cout << "\n=== listからのaddRangeテスト ===" << std::endl;
	try
	{
		std::list<int> lst;
		for (int i = 0; i < 5; ++i)
			lst.push_back(i * 10);

		Span listSpan(5);
		listSpan.addRange(lst.begin(), lst.end());
		std::cout << "Added " << listSpan.size() << " elements from list" << std::endl;
		std::cout << "Shortest span: " << listSpan.shortestSpan() << std::endl;
		std::cout << "Longest span: " << listSpan.longestSpan() << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== dequeからのaddRangeテスト ===" << std::endl;
	try
	{
		std::deque<int> deq;
		for (int i = 0; i < 7; ++i)
			deq.push_back(i * 3);

		Span dequeSpan(7);
		dequeSpan.addRange(deq.begin(), deq.end());
		std::cout << "Added " << dequeSpan.size() << " elements from deque" << std::endl;
		std::cout << "Shortest span: " << dequeSpan.shortestSpan() << std::endl;
		std::cout << "Longest span: " << dequeSpan.longestSpan() << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== ちょうど_maxSizeに到達するaddRangeテスト ===" << std::endl;
	try
	{
		Span exact(10);
		std::vector<int> firstHalf(5, 1);   // 1を5個
		std::vector<int> secondHalf(5, 2); // 2を5個

		exact.addRange(firstHalf.begin(), firstHalf.end());   // 5個追加
		exact.addRange(secondHalf.begin(), secondHalf.end()); // 残り5個追加（合計10）

		std::cout << "Successfully filled exact capacity: " << exact.size() 
		          << " / " << exact.getMaxSize() << std::endl;
		std::cout << "Shortest span: " << exact.shortestSpan() << std::endl;
		std::cout << "Longest span: " << exact.longestSpan() << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}


	return 0;
}


// additional flag : 
