#pragma once
#include <cstdint>
#include <vector>

class Element
{
private:
    uint32_t id;
    std::vector<uint32_t> tags;
    std::vector<uint32_t> points;
    uint32_t type;
    //std::vector<Element *> neighbours;
public:
    Element(uint32_t id, uint32_t type, const std::vector<uint32_t> &tags, const std::vector<uint32_t> &points) : id(id), type(type), tags(std::move(tags)), points(std::move(points))
	{
		
	}
};
