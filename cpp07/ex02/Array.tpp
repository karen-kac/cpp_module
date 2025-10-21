#ifndef ARRAY_TPP
#define ARRAY_TPP

template<typename T>
Array<T>::Array() : _elements(NULL), _size(0) {
}

template<typename T>
Array<T>::Array(unsigned int n) : _elements(NULL), _size(n) {
	if (n > 0) {
		_elements = new T[n]();
	}
}

template<typename T> 
Array<T>::Array(const Array& other) : _elements(NULL), _size(other._size) {
	if (_size > 0) {
		_elements = new T[_size]();
		for (unsigned int i = 0; i < _size; i++) {
			_elements[i] = other._elements[i];
		}
	}
}

template<typename T>
Array<T>& Array<T>::operator=(const Array& other) {
	if (this != &other) {
		// 既存リソースの解放
		delete[] _elements;
		
		// 新しいデータをコピー
		_size = other._size;
		if (_size > 0) {
			_elements = new T[_size];
			for (unsigned int i = 0; i < _size; i++) {
				_elements[i] = other._elements[i];
			}
		} else {
			_elements = NULL;
		}
	}
	return *this;
}

template<typename T>
Array<T>::~Array() {
	delete[] _elements;
}

template<typename T>
T& Array<T>::operator[](unsigned int index) {
	if (index >= _size) {
		throw std::exception();
	}
	return _elements[index];
}

template<typename T>
const T& Array<T>::operator[](unsigned int index) const {
	if (index >= _size) {
		throw std::exception();
	}
	return _elements[index];
}

template<typename T>
unsigned int Array<T>::size() const {
	return _size;
}

#endif