#include "Fixed.hpp"

bool bsp(Point const a, Point const b, Point const c, Point const point)
{

/*
    float a1 = b.getX() - a.getX();
    float b1 = b.getY() - a.getY();
    float a2 = c.getX() - a.getX();
    float b2 = c.getY() - a.getY();
    float a3 = point.getX() - a.getX();
    float b3 = point.getY() - a.getY();
    float d1 = (a1 * b3) - (a3 * b1);
    float d2 = (a3 * b2) - (a2 * b3);
    float d3 = (a2 * b1) - (a1 * b2);
*/

    // Calculate the barc.getY()entric coordinates of the point with respect to the triangle
    float denominator = ((b.getY() - c.getY()) * (a.getX() - c.getX()) + (c.getX() - b.getX()) * (a.getY() - c.getY()));
    float lambda1 = ((b.getY() - c.getY()) * (point.getX() - c.getX()) + (c.getX() - b.getX()) * (point.getY() - c.getY())) / denominator;
    float lambda2 = ((c.getY() - a.getY()) * (point.getX() - c.getX()) + (a.getX() - c.getX()) * (point.getY() - c.getY())) / denominator;
    float lambda3 = 1.0f - lambda1 - lambda2;
    printf(" hello world\n");

    // Check if the point is inside the triangle
    return (lambda1 >= 0 && lambda1 <= 1) &&
           (lambda2 >= 0 && lambda2 <= 1) &&
           (lambda3 >= 0 && lambda3 <= 1);
}

/*
    printf("a1: %f, b1: %f, a2: %f, b2: %f, a3: %f, b3: %f, d1: %f, d2: %f, d3: %f\n", a1, b1, a2, b2, a3, b3, d1, d2, d3);
    if ((d1 >= 0 && d2 >= 0 && d3 >= 0) || (d1 <= 0 && d2 <= 0 && d3 <= 0))
        return true;
        */