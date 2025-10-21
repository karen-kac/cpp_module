#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <exception>

template<typename T>
class Array {
private:
	T* _elements;
	unsigned int _size;

public:
	Array();
	Array(unsigned int n);
	Array(const Array& other);
	Array& operator=(const Array& other);
	~Array();
	
	// 添字演算子
	T& operator[](unsigned int index);
	const T& operator[](unsigned int index) const;
	
	// サイズ取得
	unsigned int size() const;
};

#include "Array.tpp"

#endif