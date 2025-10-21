#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include <string>

// データ構造体
struct Data {
	std::string str;
	int number;
};

class Serializer {
private:
	// インスタンス化禁止
	Serializer();
	Serializer(const Serializer& other);
	Serializer& operator=(const Serializer& other);
	~Serializer();

public:
	// C++98では uintptr_t が標準化されていないため unsigned long を使用
	// 64bit環境では size_t や unsigned long long も考慮が必要
	static unsigned long serialize(Data* ptr);
	static Data* deserialize(unsigned long raw);
};

#endif