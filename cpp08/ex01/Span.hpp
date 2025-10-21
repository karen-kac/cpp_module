#ifndef SPAN_HPP
#define SPAN_HPP

#include <vector>
#include <stdexcept>
#include <algorithm>

class Span
{
private:
	unsigned int _maxSize;
	std::vector<int> _numbers;

public:
	class FullContainerException : public std::exception
	{
	public:
		virtual const char* what() const throw();
	};

	class NoSpanException : public std::exception
	{
	public:
		virtual const char* what() const throw();
	};

	class RangeTooBigException : public std::exception
	{
	public:
		virtual const char* what() const throw();
	};
	Span();
	Span(unsigned int n);
	Span(const Span& other);
	Span& operator=(const Span& other);
	~Span();

	void addNumber(int number);
	
	template<typename Iterator>
	void addRange(Iterator first, Iterator last);
	
	unsigned int shortestSpan() const;
	unsigned int longestSpan() const;
	
	unsigned int size() const;
	unsigned int getMaxSize() const;
};

template<typename Iterator>
void Span::addRange(Iterator first, Iterator last)
{
	unsigned int distance = std::distance(first, last);
	if (_numbers.size() + distance > _maxSize)
		throw RangeTooBigException();
	
	_numbers.insert(_numbers.end(), first, last);
}

#endif
