#include "Point.hpp"

Point::Point() : _x(0), _y(0) {
}

Point::Point(const float xVal, const float yVal) : _x(xVal), _y(yVal) {
}

Point::Point(const Point& other) : _x(other._x), _y(other._y) {
}

Point& Point::operator=(const Point& rhs) {
	if (this != &rhs){
	}
	return *this;
}


Point::~Point() {
}

Fixed Point::getX() const {
	return this->_x;
}

Fixed Point::getY() const {
	return this->_y;
}