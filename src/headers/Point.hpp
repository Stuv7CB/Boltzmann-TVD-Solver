#pragma once

class Point
{
public:
    double x;
    double y;
    double z;
    explicit Point(const double &x, const double &y, const double &z) : x(x), y(y), z(z)
    {}
};

Point operator + (const Point &p1, const Point &p2)
{
    return Point(p1.x+p2.x, p1.y+p2.y, p1.z+p2.z);
}

Point operator - (const Point &p1, const Point &p2)
{
    return Point(p1.x-p2.x, p1.y-p2.y, p1.z-p2.z);
}

double operator * (const Point &p1, const Point &p2)
{
    return p1.x * p2.x + p1.y * p2.y + p1.z * p2.z;
}

Point operator & (const Point &p1, const Point &p2)
{
    double x = p1.y * p2.z - p2.y * p1.z;
    double y = p1.z * p2.x - p2.z * p1.x;
    double z = p1.x * p2.y - p2.x * p1.z;
    return Point(x, y, z);
}
