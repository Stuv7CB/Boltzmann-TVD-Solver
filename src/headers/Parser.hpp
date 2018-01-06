#pragma once
#include <fstream>
#include <vector>
#include "Element.hpp"
#include "Node.hpp"
#include <string>
#include <sstream>
#include <algorithm>

class Parser
{
public:
    static Node parseNode(const std::string &line)
    {
        std::stringstream stream;
        stream << line;
        uint32_t id;
        double x, y, z;
        stream >> id >> x >> y >> z;
        return Node(x, y, z, id);
    }

    static Element parseElement(const std::string &line)
    {
        std::stringstream stream;
        stream << line;
        uint32_t id, type, numberOfTags;
        stream >> id >> type >> numberOfTags;
        std::vector<uint32_t> tags;
        std::vector<uint32_t> nodes;
        for (auto i = 0; i < numberOfTags; i++)
        {
            uint32_t tag;
            stream >> tag;
            tags.emplace_back(tag);
        }
        std::string point;
        while (std::getline(stream, point, ' '))
        {
            if(point.empty())
            {
                continue;
            }
            nodes.emplace_back(std::stoi(point));
        }
        return Element(id, type, tags, nodes);
    }

	static void parse(std::ifstream &file, std::vector<Node> &nodes, std::vector<Element> &elements)
	{
		std::string line;
		while(std::getline(file, line))
		{
			if(line.compare("$Nodes") == 0)
			{
				std::getline(file, line);
				uint32_t size;
				std::stringstream stream;
				stream << line;
				stream >> size;
				while (std::getline(file, line))
				{
					if (line.compare("$EndNodes") == 0)
					{
						break;
					}
                    nodes.emplace_back(parseNode(line));
				}
			}
			if(line.compare("$Elements") == 0)
			{
				std::getline(file, line);
				uint32_t size;
				std::stringstream stream;
				stream << line;
				stream >> size;
				while (std::getline(file, line))
				{
					if (line.compare("$EndElements") == 0)
					{
						break;
					}

                    auto element = parseElement(line);

                    elements.emplace_back(element);
				}
			}
		}
	}
};
