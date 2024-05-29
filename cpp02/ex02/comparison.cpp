#include "Fixed.hpp"


bool Fixed::operator>(const Fixed &fixed) const
{
    return raw > fixed.raw;
}

bool Fixed::operator<(const Fixed &fixed) const
{
    return raw < fixed.raw;
}

bool Fixed::operator>=(const Fixed &fixed) const
{
    return raw >= fixed.raw;
}

bool Fixed::operator<=(const Fixed &fixed) const
{
    return raw <= fixed.raw;
}

bool Fixed::operator==(const Fixed &fixed) const
{
    return raw == fixed.raw;
}

bool Fixed::operator!=(const Fixed &fixed) const
{
    return raw != fixed.raw;
}
