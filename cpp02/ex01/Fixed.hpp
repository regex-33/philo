#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>
#include <cmath>

class Fixed
{
    private:
        int raw;
        static const int bits = 8;
    public:
        Fixed( void );
        Fixed( Fixed const & src );
        Fixed( int const n );
        Fixed( float const n );
        ~Fixed( void );
        Fixed & operator=( Fixed const & rhs );
        int toInt( void ) const;
        float toFloat( void ) const;
        void setRawBits( int const raw );
};
#endif

