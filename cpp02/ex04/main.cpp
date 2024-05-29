#include "Fixed.hpp"


int main()
{
    Point a(2, 2);
    Point b(2, 5);
    Point c(8, 5);
    Point point(9, 9);


    if (bsp(a, b, c, point))
        printf("Point is inside the triangle\n");
    else
        printf("Point is outside the triangle\n");
    return 0;
}