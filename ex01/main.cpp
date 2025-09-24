#include "Serializer.hpp"
#include <iostream>

int main() {
	// 元のデータを作成
	Data data;
	data.str = "Hello 42!";
	data.number = 1337;

	std::cout << "=== Original Data ===" << std::endl;
	std::cout << "Address: " << &data << std::endl;
	std::cout << "str: " << data.str << std::endl;
	std::cout << "number: " << data.number << std::endl;

	// serialize
	uintptr_t raw = Serializer::serialize(&data);
	std::cout << "\n=== After serialize ===" << std::endl;
	std::cout << "raw (uintptr_t): " << raw << std::endl;

	// deserialize
	Data* restored = Serializer::deserialize(raw);
	std::cout << "\n=== After deserialize ===" << std::endl;
	std::cout << "Address: " << restored << std::endl;
	std::cout << "str: " << restored->str << std::endl;
	std::cout << "number: " << restored->number << std::endl;

	// アドレスが一致するか確認
	if (restored == &data)
		std::cout << "\n✅ Success: Restored pointer matches original!" << std::endl;
	else
		std::cout << "\n❌ Error: Restored pointer does not match original." << std::endl;

	return 0;
}
