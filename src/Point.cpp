#include "Point.h"
#include "Station.h"


Point::Point() = default;;

Point::Point(int x, int y)
{
    this->x = x;
    this->y = y;
}

void Point::setX(int newX)
{
    x = newX;
}

int Point::getX()
{
    return x;
}

void Point::setY(int newY)
{
    y = newY;
}

int Point::getY()
{
    return y;
}

std::ostream &operator<<(std::ostream &os, const Point &point) {
    os << "x: " << point.x << " y: " << point.y;
    return os;
}
