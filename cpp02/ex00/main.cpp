#include "Fixed.hpp"

int main( void )
{
    Fixed a;
    printf("i am here\n");
    
    Fixed b = a;
    printf("i am here\n");
    // Fixed c;
    // c = b;
    std::cout << a.getRawBits() << std::endl;
    std::cout << b.getRawBits() << std::endl;
    //std::cout << c.getRawBits() << std::endl;
    return 0;
}