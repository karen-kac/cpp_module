#include "Serializer.hpp"

// Data* → unsigned long
// serializeはビット列をそのまま別の型として返す
unsigned long Serializer::serialize(Data* ptr) {
	return reinterpret_cast<unsigned long>(ptr);
}

// unsigned long → Data*
Data* Serializer::deserialize(unsigned long raw) {
	return reinterpret_cast<Data*>(raw);
}