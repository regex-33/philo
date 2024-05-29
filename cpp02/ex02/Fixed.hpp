#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>

class Fixed
{
    private:
        int raw;
        static const int _fractionalBits = 8;
    public:
        Fixed();
        Fixed(const Fixed &fixed);
        Fixed(const int value);
        Fixed(const float value);
        ~Fixed();
        Fixed &operator=(const Fixed &fixed);


        static Fixed &min(Fixed &a, Fixed &b)
        {
            printf("min\n");
            return a < b ? a : b;
        }
        static Fixed &max(Fixed &a, Fixed &b)
        {
            printf("max\n");
            return a > b ? a : b;
        }
        static const Fixed &min(const Fixed &a, const Fixed &b)
        {
            printf("const min\n");
            return a < b ? a : b;
        }
    
        static const Fixed &max(const Fixed &a, const Fixed &b)
        {
            printf("const max\n");
            return a > b ? a : b;
        }

        Fixed operator+(const Fixed &fixed) const;
        Fixed operator-(const Fixed &fixed) const;
        Fixed operator*(const Fixed &fixed) const;
        Fixed operator/(const Fixed &fixed) const;
        Fixed &operator++();
        Fixed operator++(int);
        Fixed &operator--();
        Fixed operator--(int);

        bool operator>(const Fixed &fixed) const;
        bool operator<(const Fixed &fixed) const;
        bool operator>=(const Fixed &fixed) const;
        bool operator<=(const Fixed &fixed) const;
        bool operator==(const Fixed &fixed) const;
        bool operator!=(const Fixed &fixed) const;
        int getRawBits(void) const;
        void setRawBits(int const raw);
        float toFloat(void) const;
        int toInt(void) const;

};

#endif