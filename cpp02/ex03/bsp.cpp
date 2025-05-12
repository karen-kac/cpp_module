#include "Point.hpp"

static Fixed area(Point const &a, Point const &b, Point const &c)
{
	// Area = 0.5 * |x1(y2 - y3) + x2(y3 - y1) + x3(y1 - y2)|
	Fixed area = ((a.getX() * (b.getY() - c.getY())) +
				  (b.getX() * (c.getY() - a.getY())) +
				  (c.getX() * (a.getY() - b.getY()))) / Fixed(2);
	
	if (area < Fixed(0))
		area = area * Fixed(-1);
	
	return area;
}

bool bsp(Point const a, Point const b, Point const c, Point const point)
{
	Fixed areaABC = area(a, b, c);

	Fixed areaPBC = area(point, b, c);
	Fixed areaPAC = area(a, point, c);
	Fixed areaPAB = area(a, b, point);

	// std::cout << "areaPBC: " << areaPBC << std::endl;
	// std::cout << "areaPAC: " << areaPAC << std::endl;
	// std::cout << "areaPAB: " << areaPAB << std::endl;
	if (areaPBC == Fixed(0) || areaPAC == Fixed(0) || areaPAB == Fixed(0))
		return false;

	Fixed sumAreas = areaPBC + areaPAC + areaPAB;
	// std::cout << "sumAreas: " << sumAreas << std::endl;
	// std::cout << "areaABC: " << areaABC << std::endl;
	Fixed epsilon = Fixed(0.01f);
	// std::cout << "sumAreas - areaABC: " << sumAreas - areaABC << std::endl;
	// std::cout << "epsilon: " << epsilon << std::endl;
	if (sumAreas - areaABC < epsilon)
		return true;
	return false;
}