#include <iostream>
#include <string>
#include "Array.hpp"

void testIntArray() {
	std::cout << "=== 整数配列のテスト ===" << std::endl;
	
	try {
		// デフォルトコンストラクタのテスト
		Array<int> emptyArray;
		std::cout << "空配列のサイズ: " << emptyArray.size() << std::endl;
		
		// サイズ指定コンストラクタのテスト
		Array<int> intArray(5);
		std::cout << "int配列のサイズ: " << intArray.size() << std::endl;
		
		// デフォルト初期化の確認
		std::cout << "デフォルト値: ";
		for (unsigned int i = 0; i < intArray.size(); i++) {
			std::cout << intArray[i] << " ";
		}
		std::cout << std::endl;
		
		// 代入のテスト
		for (unsigned int i = 0; i < intArray.size(); i++) {
			intArray[i] = (i + 1) * 10;
		}
		
		std::cout << "代入後: ";
		for (unsigned int i = 0; i < intArray.size(); i++) {
			std::cout << intArray[i] << " ";
		}
		std::cout << std::endl;
		
		// コピーコンストラクタのテスト
		Array<int> copyArray(intArray);
		std::cout << "コピー配列のサイズ: " << copyArray.size() << std::endl;
		std::cout << "コピー配列の値: ";
		for (unsigned int i = 0; i < copyArray.size(); i++) {
			std::cout << copyArray[i] << " ";
		}
		std::cout << std::endl;
		
		// 元配列の変更でディープコピーを確認
		intArray[0] = 999;
		std::cout << "元配列の変更後: " << intArray[0] << std::endl;
		std::cout << "コピー配列(元の変更の影響なし): " << copyArray[0] << std::endl;
		
		// 代入演算子のテスト
		Array<int> assignArray;
		assignArray = intArray;
		std::cout << "代入後配列のサイズ: " << assignArray.size() << std::endl;
		std::cout << "代入後配列の先頭要素: " << assignArray[0] << std::endl;
		
		// 範囲外アクセスのテスト
		std::cout << "範囲外アクセスをテスト中..." << std::endl;
		std::cout << intArray[10] << std::endl;  // 例外が投げられるはず
		
	} catch (const std::exception& e) {
		std::cout << "例外を捕捉: " << e.what() << std::endl;
	}
}

void testStringArray() {
	std::cout << "\n=== 文字列配列のテスト ===" << std::endl;
	
	try {
		Array<std::string> stringArray(3);
		std::cout << "文字列配列のサイズ: " << stringArray.size() << std::endl;
		
		// 文字列のデフォルト初期化の確認
		std::cout << "デフォルトの文字列: ";
		for (unsigned int i = 0; i < stringArray.size(); i++) {
			std::cout << "[" << stringArray[i] << "] ";
		}
		std::cout << std::endl;
		
		// 値の代入
		stringArray[0] = "Hello";
		stringArray[1] = "World";
		stringArray[2] = "Templates";
		
		std::cout << "代入後: ";
		for (unsigned int i = 0; i < stringArray.size(); i++) {
			std::cout << "[" << stringArray[i] << "] ";
		}
		std::cout << std::endl;
		
		// constアクセスのテスト
		const Array<std::string>& constRef = stringArray;
		std::cout << "const参照でのアクセス: " << constRef[1] << std::endl;
		
	} catch (const std::exception& e) {
		std::cout << "例外を捕捉: " << e.what() << std::endl;
	}
}

void testEmptyArray() {
	std::cout << "\n=== 空配列の操作テスト ===" << std::endl;
	
	try {
		Array<int> emptyArray;
		std::cout << "空配列のサイズ: " << emptyArray.size() << std::endl;
		
		// これは例外になるはず
		std::cout << "空配列の要素0へアクセスを試みる..." << std::endl;
		std::cout << emptyArray[0] << std::endl;
		
	} catch (const std::exception& e) {
		std::cout << "例外を捕捉: " << e.what() << std::endl;
	}
}

int main(void) {
	testIntArray();
	testStringArray();
	testEmptyArray();
	return 0;
}

// #include <iostream>
// #include "Array.hpp"

// #define MAX_VAL 750
// int main(int, char**)
// {
// 	Array<int> numbers(MAX_VAL);
// 	int* mirror = new int[MAX_VAL];
// 	srand(time(NULL));
// 	for (int i = 0; i < MAX_VAL; i++)
// 	{
// 		const int value = rand();
// 		numbers[i] = value;
// 		mirror[i] = value;
// 	}
// 	//SCOPE
// 	{
// 		Array<int> tmp = numbers;
// 		Array<int> test(tmp);
// 	}

// 	for (int i = 0; i < MAX_VAL; i++)
// 	{
// 		if (mirror[i] != numbers[i])
// 		{
// 			std::cerr << "didn't save the same value!!" << std::endl;
// 			return 1;
// 		}
// 	}
// 	try
// 	{
// 		numbers[-2] = 0;
// 	}
// 	catch(const std::exception& e)
// 	{
// 		std::cerr << e.what() << '\n';
// 	}
// 	try
// 	{
// 		numbers[MAX_VAL] = 0;
// 	}
// 	catch(const std::exception& e)
// 	{
// 		std::cerr << e.what() << '\n';
// 	}

// 	for (int i = 0; i < MAX_VAL; i++)
// 	{
// 		numbers[i] = rand();
// 	}
// 	delete [] mirror;//
// 	return 0;
// }
