#include "Fixed.hpp"

Fixed::Fixed( void ) : raw(0)
{
    std::cout << "Default constructor called" << std::endl;
}
Fixed::Fixed( Fixed const & src )
{
    std::cout << "Copy constructor called" << std::endl;
    *this = src;
}

Fixed::~Fixed( void )
{
    std::cout << "Destructor called" << std::endl;
}


Fixed &Fixed::operator=( const Fixed &otherfixed )
{
    std::cout << "Assignation operator called" << std::endl;
    if (this != &otherfixed)
        this->raw = otherfixed.getRawBits();
    return *this;
}

int Fixed::getRawBits( void ) const
{
    std::cout << "getRawBits member function called" << std::endl;
    return this->raw;
}


void Fixed::setRawBits( int const raw )
{
    std::cout << "setRawBits member function called" << std::endl;
    this->raw = raw;
}
