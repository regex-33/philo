#include "Fixed.hpp"

Fixed &Fixed::operator++()
{
    printf("++++++number\n ");
    raw++;
    return *this;
}

Fixed Fixed::operator++(int)
{
    printf("number++++++\n ");
    Fixed tmp(*this);
    operator++();
    return tmp;
}

Fixed &Fixed::operator--()
{
    raw--;
    return *this;
}

Fixed Fixed::operator--(int)
{
    Fixed tmp(*this);
    operator--();
    return tmp;
}

