#include "Fixed.hpp"

Fixed Fixed::operator+(const Fixed &fixed) const
{
    printf("plus\n");
    return Fixed(toFloat() + fixed.toFloat());
}

Fixed Fixed::operator-(const Fixed &fixed) const
{
    return Fixed(toFloat() - fixed.toFloat());
}

Fixed Fixed::operator*(const Fixed &fixed) const
{
    printf(" njma \n");
    printf("float %f\n", toFloat());
    printf("fixed float %f\n", fixed.toFloat());
    return Fixed(toFloat() * fixed.toFloat());
}


Fixed Fixed::operator/(const Fixed &fixed) const
{
    return Fixed(toFloat() / fixed.toFloat());
}