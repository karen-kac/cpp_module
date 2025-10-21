#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <exception>  // std::exception用

// ランダムにA, B, Cを生成
Base* generate(void) {
	static bool seeded = false;
	if (!seeded) {
		std::srand(static_cast<unsigned int>(std::time(0)));
		seeded = true;
	}

	int random = std::rand() % 3;
	switch (random) {
		case 0:
			std::cout << "Generated: A" << std::endl;
			return new A();
		case 1:
			std::cout << "Generated: B" << std::endl;
			return new B();
		default:
			std::cout << "Generated: C" << std::endl;
			return new C();
	}
}

// 実際の型を出力（ポインタ版）
// 失敗するとNULLを返す
void identify(Base* p) {
	if (dynamic_cast<A*>(p)) {
		std::cout << "A" << std::endl;
	} else if (dynamic_cast<B*>(p)) {
		std::cout << "B" << std::endl;
	} else if (dynamic_cast<C*>(p)) {
		std::cout << "C" << std::endl;
	} else {
		std::cout << "Unknown type" << std::endl;
	}
}

// 実際の型を出力（参照版）
// 失敗すると例外を投げる
void identify(Base& p) {
	try {
		A& a = dynamic_cast<A&>(p);
		(void)a;  // unused variable warning回避
		std::cout << "A" << std::endl;
		return;
	} catch (const std::exception&) {
		// Aではない、次を試す
	}

	try {
		B& b = dynamic_cast<B&>(p);
		(void)b;  // unused variable warning回避
		std::cout << "B" << std::endl;
		return;
	} catch (const std::exception&) {
		// Bではない、次を試す
	}

	try {
		C& c = dynamic_cast<C&>(p);
		(void)c;  // unused variable warning回避
		std::cout << "C" << std::endl;
		return;
	} catch (const std::exception&) {
		// Cでもない
	}

	std::cout << "Unknown type" << std::endl;
}

int main() {
	std::cout << "=== Exercise 02: Identify real type ===" << std::endl;

	// 複数回テスト
	for (int i = 0; i < 5; ++i) {
		std::cout << "\n--- Test " << (i + 1) << " ---" << std::endl;
		
		Base* obj = generate();

		std::cout << "identify(Base* p): ";
		identify(obj);
		
		// 参照でテスト
		std::cout << "identify(Base& p): ";
		identify(*obj);
		
		// メモリを解放
		delete obj;
	}

	std::cout << "\n=== Additional Tests ===" << std::endl;
	
	// 各型を明示的にテスト
	std::cout << "\nExplicit A test:" << std::endl;
	Base* a = new A();
	std::cout << "identify(A* as Base*): ";
	identify(a);
	std::cout << "identify(A& as Base&): ";
	identify(*a);
	delete a;

	std::cout << "\nExplicit B test:" << std::endl;
	Base* b = new B();
	std::cout << "identify(B* as Base*): ";
	identify(b);
	std::cout << "identify(B& as Base&): ";
	identify(*b);
	delete b;

	std::cout << "\nExplicit C test:" << std::endl;
	Base* c = new C();
	std::cout << "identify(C* as Base*): ";
	identify(c);
	std::cout << "identify(C& as Base&): ";
	identify(*c);
	delete c;

	return 0;
}