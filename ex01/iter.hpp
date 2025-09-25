#ifndef ITER_HPP
#define ITER_HPP

#include <cstddef>

// 非const配列の時
template<typename T, typename Func>
void iter(T* array, std::size_t length, Func func) {
	for (size_t i = 0; i < length; i++) {
		func(array[i]);
	}
}

// const配列の時
template<typename T, typename Func>
void iter(const T* array, std::size_t length, Func func) {
	for (size_t i = 0; i < length; i++) {
		func(array[i]);
	}
}

#endif
