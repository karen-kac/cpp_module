#include <iostream>
#include <string>

int main()
{
	std::string stringVAR = "HI THIS IS BRAIN";
	std::string* stringPTR = &stringVAR;
	std::string& stringREF = stringVAR;

	std::cout << "メモリアドレス:" << std::endl;
	std::cout << "stringVAR のアドレス: " << &stringVAR << std::endl;
	std::cout << "stringPTR が指すアドレス: " << stringPTR << std::endl;
	std::cout << "stringREF のアドレス: " << &stringREF << std::endl;

	std::cout << "\n値:" << std::endl;
	std::cout << "stringVAR の値: " << stringVAR << std::endl;
	std::cout << "stringPTR が指す値: " << *stringPTR << std::endl;
	std::cout << "stringREF の値: " << stringREF << std::endl;

	std::cout << "\n変数の値を変更:" << std::endl;
	stringVAR = "BRAIN HAS BEEN MODIFIED";
	std::cout << "stringVAR の新しい値: " << stringVAR << std::endl;
	std::cout << "stringPTR が指す新しい値: " << *stringPTR << std::endl;
	std::cout << "stringREF の新しい値: " << stringREF << std::endl;

	std::cout << "\nポインタを通じて値を変更:" << std::endl;
	*stringPTR = "POINTER MODIFIED THE BRAIN";
	std::cout << "stringVAR の新しい値: " << stringVAR << std::endl;
	std::cout << "stringPTR が指す新しい値: " << *stringPTR << std::endl;
	std::cout << "stringREF の新しい値: " << stringREF << std::endl;

	std::cout << "\n参照を通じて値を変更:" << std::endl;
	stringREF = "REFERENCE MODIFIED THE BRAIN";
	std::cout << "stringVAR の新しい値: " << stringVAR << std::endl;
	std::cout << "stringPTR が指す新しい値: " << *stringPTR << std::endl;
	std::cout << "stringREF の新しい値: " << stringREF << std::endl;
	
	return 0;
}


// If you pass a pointer, you should check for null.
// References are constrained pointers