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

					uint32_t id;
					double x, y, z;
					stream.str("");
					stream.clear();
					stream << line;
					stream >> id >> x >> y >> z;
					nodes.emplace_back(x, y, z, id);
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

					uint32_t id, type, numTag, physId, t;
					stream.str("");
					stream.clear();
					stream << line;
					stream >> id >> type >> numTag;
					for (auto i = 0; i < numTag; i++)
					{
						if (i == 0)
						{
							stream >> physId;
							continue;
						}
						stream >> t;
					}
					std::vector<uint32_t> points;
					std::string st;
					while (std::getline(stream, st, ' '))
					{
						if(st.empty())
						{
							continue;
						}
						points.push_back(std::stoi(st));
					}
					std::vector<Element *> neigh;
					elements.emplace_back(id, type, physId, points);
					for (auto iter = elements.begin(); iter != (elements.end() - 1); ++iter)
					{
						auto it = std::find_if(iter, elements.end()-1, [&](Element el)->bool
						{
							int i = 0;
							for (auto point : points)
							{
								if (std::find(iter->points.begin(), iter->points.end(), point) != iter->points.end())
								{
									i++;
								}
							}
							if (i == 3)
							{
								return true;
							}
							return false;
						});
						if (it != (elements.end() - 1))
						{
							neigh.push_back(&(*it));
							iter = it;
							it->neighbours.push_back(&(*((elements.end() - 1))));
						}
						else
						{
							break;
						}
					}
					(elements.end() - 1)->neighbours = neigh;
				}
			}
		}
	}
};
