#pragma once
#include <cstdint>
#include <vector>

struct Element
{
	const uint32_t id;
	const uint32_t phys;
	const std::vector<uint32_t> points;
	const uint32_t type;
	std::vector<Element *> neighbours;
	Element(uint32_t id, uint32_t type, uint32_t phys, const std::vector<uint32_t> &points) : id(id), type(type), phys(phys), points(points)
	{
		
	}
};
