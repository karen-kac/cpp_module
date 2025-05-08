#include "Fixed.hpp"
#include "Fixed.hpp"

Fixed::Fixed() : _rawBits(0)
{
	// std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const Fixed& other)
{
	// std::cout << "Copy constructor called" << std::endl;
	*this = other;
}

Fixed& Fixed::operator=(const Fixed& src) {
	// std::cout << "Copy assignment operator called" << std::endl;
	if (this != &src) {
		this->_rawBits = src.getRawBits();
	}
	return *this;
}

Fixed::~Fixed() {
	// std::cout << "Destructor called" << std::endl;
}

Fixed::Fixed(const float floatValue)
{
	// std::cout << "Float constructor called" << std::endl;
	_rawBits = roundf(floatValue * (1 << _fractionalBits));
}

Fixed::Fixed(const int intValue)
{
	// std::cout << "Int constructor called" << std::endl;
	_rawBits = intValue << _fractionalBits;
}

int Fixed::getRawBits(void) const
{
	// std::cout << "getRawBits member function called" << std::endl;
	return this->_rawBits;
}

void Fixed::setRawBits(int const raw)
{
	this->_rawBits = raw;
}

float Fixed::toFloat(void) const
{
	return static_cast<float>(_rawBits) / (1 << _fractionalBits);
}

int Fixed::toInt(void) const
{
	return _rawBits >> _fractionalBits;
}

bool Fixed::operator>(const Fixed& rhs) const {
	return this->_rawBits > rhs._rawBits;
}

bool Fixed::operator<(const Fixed& rhs) const {
	return this->_rawBits < rhs._rawBits;
}

bool Fixed::operator>=(const Fixed& rhs) const {
	return this->_rawBits >= rhs._rawBits;
}

bool Fixed::operator<=(const Fixed& rhs) const {
	return this->_rawBits <= rhs._rawBits;
}

bool Fixed::operator==(const Fixed& rhs) const {
	return this->_rawBits == rhs._rawBits;
}

bool Fixed::operator!=(const Fixed& rhs) const {
	return this->_rawBits != rhs._rawBits;
}


Fixed Fixed::operator+(const Fixed& rhs) const
{
	Fixed result;
	result.setRawBits(this->_rawBits + rhs._rawBits);
	return result;
}

Fixed Fixed::operator-(const Fixed& rhs) const
{
	Fixed result;
	result.setRawBits(this->_rawBits - rhs._rawBits);
	return result;
}

Fixed Fixed::operator*(const Fixed& rhs) const
{
	Fixed result;
	result.setRawBits((this->_rawBits * rhs._rawBits) >> _fractionalBits);
	return result;
}

Fixed Fixed::operator/(const Fixed& rhs) const
{

	if (rhs._rawBits == 0) {
		std::cerr << "Error: Division by zero" << std::endl;
		return Fixed();
	}

	Fixed result;
	result.setRawBits((this->_rawBits << _fractionalBits) / rhs._rawBits);
	return result;
}

Fixed& Fixed::operator++()
{
	++this->_rawBits;
	return *this;
}

Fixed Fixed::operator++(int)
{
	Fixed temp(*this);
	++(*this);
	return temp;
}

Fixed& Fixed::operator--()
{
	--this->_rawBits;
	return *this;
}

Fixed Fixed::operator--(int)
{
	Fixed temp(*this);
	--(*this);
	return temp;
}

Fixed& Fixed::min(Fixed& a, Fixed& b)
{
	return (a < b) ? a : b;
}

const Fixed& Fixed::min(const Fixed& a, const Fixed& b)
{
	return (a < b) ? a : b;
}

Fixed& Fixed::max(Fixed& a, Fixed& b)
{
	return (a > b) ? a : b;
}

const Fixed& Fixed::max(const Fixed& a, const Fixed& b) {
	return (a > b) ? a : b;
}

std::ostream& operator<<(std::ostream& os, const Fixed& fixed) {
	os << fixed.toFloat();
	return os;
}