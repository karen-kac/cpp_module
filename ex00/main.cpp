#include <iostream>
#include <string>
#include "whatever.hpp"

int main(void) {
	int a = 2;
	int b = 3;
	
	::swap(a, b);
	std::cout << "a = " << a << ", b = " << b << std::endl;
	std::cout << "min( a, b ) = " << ::min(a, b) << std::endl;
	std::cout << "max( a, b ) = " << ::max(a, b) << std::endl;
	
	std::string c = "chaine1";
	std::string d = "chaine2";
	
	::swap(c, d);
	std::cout << "c = " << c << ", d = " << d << std::endl;
	std::cout << "min( c, d ) = " << ::min(c, d) << std::endl;
	std::cout << "max( c, d ) = " << ::max(c, d) << std::endl;
	
	return 0;
}

// #include <iostream>
// #include <string>
// #include "whatever.hpp"

// struct Point { int x; };
// std::ostream& operator<<(std::ostream& os, const Point& p) { os << "Point{" << p.x << "}"; return os; }
// bool operator<(const Point& lhs, const Point& rhs) { return lhs.x < rhs.x; }
// bool operator>(const Point& lhs, const Point& rhs) { return lhs.x > rhs.x; }

// int main(void) {
// 	int a = 2;
// 	int b = 3;
	
// 	::swap(a, b);
// 	std::cout << "a = " << a << ", b = " << b << std::endl;
// 	std::cout << "min( a, b ) = " << ::min(a, b) << std::endl;
// 	std::cout << "max( a, b ) = " << ::max(a, b) << std::endl;
	
// 	std::string c = "chaine1";
// 	std::string d = "chaine2";
	
// 	::swap(c, d);
// 	std::cout << "c = " << c << ", d = " << d << std::endl;
// 	std::cout << "min( c, d ) = " << ::min(c, d) << std::endl;
// 	std::cout << "max( c, d ) = " << ::max(c, d) << std::endl;
	
// 	// Additional tests
// 	std::cout << "\n[ Equal integers ]" << std::endl;
// 	int e = 42;
// 	int f = 42;
// 	::swap(e, f);
// 	std::cout << "e = " << e << ", f = " << f << std::endl;
// 	std::cout << "min( e, f ) = " << ::min(e, f) << std::endl;
// 	std::cout << "max( e, f ) = " << ::max(e, f) << std::endl;

// 	std::cout << "\n[ Negative integers ]" << std::endl;
// 	int g = -5;
// 	int h = 10;
// 	::swap(g, h);
// 	std::cout << "g = " << g << ", h = " << h << std::endl;
// 	std::cout << "min( g, h ) = " << ::min(g, h) << std::endl;
// 	std::cout << "max( g, h ) = " << ::max(g, h) << std::endl;

// 	std::cout << "\n[ Doubles ]" << std::endl;
// 	double i = 3.14;
// 	double j = -2.71;
// 	::swap(i, j);
// 	std::cout << "i = " << i << ", j = " << j << std::endl;
// 	std::cout << "min( i, j ) = " << ::min(i, j) << std::endl;
// 	std::cout << "max( i, j ) = " << ::max(i, j) << std::endl;

// 	std::cout << "\n[ Equal strings ]" << std::endl;
// 	std::string k = "abc";
// 	std::string l = "abc";
// 	::swap(k, l);
// 	std::cout << "k = " << k << ", l = " << l << std::endl;
// 	std::cout << "min( k, l ) = " << ::min(k, l) << std::endl;
// 	std::cout << "max( k, l ) = " << ::max(k, l) << std::endl;

// 	std::cout << "\n[ const values (min/max only) ]" << std::endl;
// 	const int m = 7;
// 	const int n = 21;
// 	std::cout << "min( m, n ) = " << ::min(m, n) << std::endl;
// 	std::cout << "max( m, n ) = " << ::max(m, n) << std::endl;

// 	std::cout << "\n[ User-defined type ]" << std::endl;
// 	Point p = {5};
// 	Point q = {10};
// 	::swap(p, q);
// 	std::cout << "p = " << p << ", q = " << q << std::endl;
// 	std::cout << "min( p, q ) = " << ::min(p, q) << std::endl;
// 	std::cout << "max( p, q ) = " << ::max(p, q) << std::endl;

// 	return 0;
// }
