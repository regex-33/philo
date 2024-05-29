#include "Fixed.hpp"

Fixed::Fixed( void ) : raw(0)
{
    std::cout << "Default constructor called" << std::endl;
}
Fixed::~Fixed( void )
{
    std::cout << "Destructor called" << std::endl;
}

Fixed::Fixed( Fixed const & src )
{
    std::cout << "Copy constructor called" << std::endl;
    *this = src;
}

Fixed::Fixed( int const n )
{
    std::cout << "Int constructor called" << std::endl;
    //  printf("n = %d\n", n);
     this->raw = n << bits;
     //raw = raw;//n << bits;
    //  printf("raw = %d\n", raw);
}

void Fixed::setRawBits( int const raw )
{
    this->raw = raw;
}

Fixed::Fixed( float const n )
{
    std::cout << "Float constructor called" << std::endl;
    //printf("const n = %f\n", n);
    this->raw = roundf(n * (1 << bits));
   // raw = n;
    // std::cout << "raw = " << raw << "  | " << (float)raw / 256 << std::endl;
// printf("after const n = %f\n", raw);
}


Fixed & Fixed::operator=( Fixed const & src )
{
    std::cout << "Assignation operator called" << std::endl;
    if (this != &src)
        this->raw = src.raw;
    return *this;
}

int Fixed::toInt( void ) const
{
    //return raw;// >> bits;
    return raw >> bits;
}

float Fixed::toFloat( void ) const
{
    return ((float)raw / (1 << bits));
    // return (float)raw;
}

