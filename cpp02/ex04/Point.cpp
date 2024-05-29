#include "Fixed.hpp"

Point::Point() : x(0), y(0)
{
    std::cout << "Default constructor called" << std::endl;
}

Point::Point(const Point &point)
{
    std::cout << "Copy constructor called" << std::endl;
    *this = point;
}

Point::Point(const float x, const float y) : x(x), y(y)
{
    std::cout << "Float constructor called" << std::endl;
}

Point &Point::operator=(const Point &point)
{
    std::cout << "Assignation operator called" << std::endl;
    if (this != &point)
    {
        x = point.x;
        y = point.y;
    }
    return *this;
}

Point::~Point()
{
    std::cout << "Destructor called" << std::endl;
}


float Point::getX() const
{
    return x;
}

float Point::getY() const
{
    return y;
}

void Point::setX(const float x)
{
    this->x = x;
}

void Point::setY(const float y)
{
    this->y = y;
}

