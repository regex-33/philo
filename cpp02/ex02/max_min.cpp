#include "Fixed.hpp"

Fixed &Fixed::min(Fixed &a, Fixed &b)
{
    printf("min\n");
    return a < b ? a : b;
}

Fixed &Fixed::max(Fixed &a, Fixed &b)
{
    printf("max\n");
    return a > b ? a : b;
}

const Fixed &Fixed::min(const Fixed &a, const Fixed &b)
{
    printf("const min\n");
    return a < b ? a : b;
}

const Fixed &Fixed::max(const Fixed &a, const Fixed &b)
{
    printf("const max\n");
    return a > b ? a : b;
}