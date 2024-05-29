#include "Fixed.hpp"
#include <math.h>


Fixed::Fixed() : raw(0)
{
    std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const Fixed &fixed)
{
    std::cout << "Copy constructor called" << std::endl;
    *this = fixed;
}

Fixed::Fixed(const int value)
{
    printf("int value: %d\n", value);
    std::cout << "Int constructor called" << std::endl;
    raw = value << _fractionalBits;
}

Fixed::Fixed(const float value)
{
    std::cout << "Float constructor called" << std::endl;
    printf("value: %f\n", value);
    raw = roundf(value * (1 << _fractionalBits));
}


Fixed &Fixed::operator=(const Fixed &fixed)
{
    std::cout << "Assignation operator called" << std::endl;
    if (this != &fixed)
        raw = fixed.raw;
    return *this;
}

int Fixed::getRawBits(void) const
{
    std::cout << "getRawBits member function called" << std::endl;
    return raw;
}

void Fixed::setRawBits(int const raw)
{
    std::cout << "setRawBits member function called" << std::endl;
    this->raw = raw;
}

float Fixed::toFloat(void) const
{
    return (float)raw / (1 << _fractionalBits);
}

int Fixed::toInt(void) const
{
    return raw >> _fractionalBits;
}

Fixed::~Fixed()
{
    std::cout << "Destructor called" << std::endl;
}
