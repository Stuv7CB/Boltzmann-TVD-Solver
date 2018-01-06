#pragma once
#include <cstdint>
#include "Point.hpp"

class Node
{
private:
    Point point;
    uint32_t id;
public:
    Node(const double &x, const double &y, const double &z, const uint32_t &id) : point(Point(x, y, z)), id(id)
	{}
};
