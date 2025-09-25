#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <exception>
#include <stdexcept>

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
	
// 範囲外アクセス時に投げる例外クラス
	class OutOfBoundsException : public std::exception {
	public:
		virtual const char* what() const throw() {
			return "Array index out of bounds";
		}
	};
};

#include "Array.tpp"

#endif


