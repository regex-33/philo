#include "Fixed.hpp"
#include <iostream>

// Define the multiplication operator for the Fixed class
#include "Fixed.hpp"
#include <iostream>

int main( void )
{
    Fixed a;
    printf("i am here\n");
    Fixed  const b( Fixed( 5.05f ) * Fixed( 2 ) );

    printf("i am here\n");
    std::cout << a.toFloat() << std::endl;
    std::cout << (++a).toFloat() << std::endl;
    std::cout << a.toFloat() << std::endl;
    std::cout << (a++).toFloat() << std::endl;
    std::cout << a.toFloat() << std::endl;
    std::cout << b.toFloat() << std::endl;
    std::cout << Fixed::max( a, b ).toFloat() << std::endl;
    return 0;
}

