#include "Point.hpp"

void test(Point const& a, Point const& b, Point const& c, Point const& p, std::string label) {
	std::cout << label << ": ";
	if (bsp(a, b, c, p))
		std::cout << "✅ Inside" << std::endl;
	else
		std::cout << "❌ Outside or on edge/vertex" << std::endl;
}

int main() {
	Point a(0, 0);
	Point b(10, 0);
	Point c(5, 10);

	std::cout << "--- 通常ケース ---" << std::endl;
	test(a, b, c, Point(5, 5), "中央");                // 明確に内部
	test(a, b, c, Point(5, 8), "上部内部");

	std::cout << "\n--- エッジケース（辺上） ---" << std::endl;
	test(a, b, c, Point(5, 0), "底辺上");              // 辺上（false）
	test(a, b, c, Point(2.5f, 5), "左辺上");
	test(a, b, c, Point(7.5f, 5), "右辺上");

	std::cout << "\n--- エッジケース（頂点上） ---" << std::endl;
	test(a, b, c, Point(0, 0), "頂点A");
	test(a, b, c, Point(10, 0), "頂点B");
	test(a, b, c, Point(5, 10), "頂点C");

	std::cout << "\n--- エッジケース（外部） ---" << std::endl;
	test(a, b, c, Point(-1, -1), "外側左下");
	test(a, b, c, Point(11, 0), "外側右");
	test(a, b, c, Point(5, 11), "外側上");

	std::cout << "\n--- 極小誤差（境界ギリギリ） ---" << std::endl;
	test(a, b, c, Point(5, 0.01f), "底辺すれすれ内側");
	test(a, b, c, Point(5, -0.01f), "底辺すれすれ外側");

	return 0;
}

// int main(void)
// {
// 	Point a(0, 0);
// 	Point b(10, 30);
// 	Point c(20, 0);

// 	Point inside(10, 15);
// 	Point outside(30, 15);
// 	Point onVertex(0, 0);
// 	Point onEdge(10, 0);
	
// 	std::cout << "Point inside: " << (bsp(a, b, c, inside) ? "Inside" : "Outside") << std::endl;
// 	std::cout << "Point outside: " << (bsp(a, b, c, outside) ? "Inside" : "Outside") << std::endl;
// 	std::cout << "Point on vertex: " << (bsp(a, b, c, onVertex) ? "Inside" : "Outside") << std::endl;
// 	std::cout << "Point on edge: " << (bsp(a, b, c, onEdge) ? "Inside" : "Outside") << std::endl;
	
// 	return 0;
// }
