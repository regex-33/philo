#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>

class Point
{
    private:
        float x;
        float y;
    public:
        Point();
        Point(const Point &point);
        Point(const float x, const float y);
        ~Point();
        Point &operator=(const Point &point);
        float getX() const;
        float getY() const;
        void setX(const float x);
        void setY(const float y);
};

bool bsp(Point const a, Point const b, Point const c, Point const point);
#endif