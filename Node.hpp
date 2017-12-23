#pragma once
#include <cstdint>

struct Node
{
	const double x;
	const double y;
	const double z;
	uint32_t id;
	Node(double x, double y, double z, uint32_t id) : x(x), y(y), z(z), id(id)
	{}
};
