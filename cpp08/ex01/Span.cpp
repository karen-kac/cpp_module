#include "Span.hpp"
#include <climits>

const char* Span::FullContainerException::what() const throw()
{
	return "Container is full";
}

const char* Span::NoSpanException::what() const throw()
{
	return "No span can be found (need at least 2 elements)";
}

const char* Span::RangeTooBigException::what() const throw()
{
	return "Range is too big for available space";
}

Span::Span() : _maxSize(0) {}

Span::Span(unsigned int n) : _maxSize(n)
{
	_numbers.reserve(n);
}

Span::Span(const Span& other) : _maxSize(other._maxSize), _numbers(other._numbers) {}

Span& Span::operator=(const Span& other)
{
	if (this != &other)
	{
		_maxSize = other._maxSize;
		_numbers = other._numbers;
	}
	return *this;
}

Span::~Span() {}

// 数値を追加
void Span::addNumber(int number)
{
	if (_numbers.size() >= _maxSize)
		throw FullContainerException();
	_numbers.push_back(number);
}

// 最短のspanを見つける
unsigned int Span::shortestSpan() const
{
	if (_numbers.size() < 2)
		throw NoSpanException();
	
	std::vector<int> sorted = _numbers;
	std::sort(sorted.begin(), sorted.end());
	
	unsigned int minSpan = UINT_MAX;
	for (size_t i = 1; i < sorted.size(); ++i)
	{
		unsigned int span = static_cast<unsigned int>(sorted[i] - sorted[i - 1]);
		if (span < minSpan)
			minSpan = span;
	}
	
	return minSpan;
}

// 最長のspanを見つける
unsigned int Span::longestSpan() const
{
	if (_numbers.size() < 2)
		throw NoSpanException();
	
	std::vector<int>::const_iterator minIt = std::min_element(_numbers.begin(), _numbers.end());
	std::vector<int>::const_iterator maxIt = std::max_element(_numbers.begin(), _numbers.end());
	
	return static_cast<unsigned int>(*maxIt - *minIt);
}

// 現在のサイズを取得
unsigned int Span::size() const
{
	return _numbers.size();
}

// 最大サイズを取得
unsigned int Span::getMaxSize() const
{
	return _maxSize;
}
