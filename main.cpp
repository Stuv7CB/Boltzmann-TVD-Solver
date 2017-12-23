#include <iostream>
#include <fstream>
#include "Parser.hpp"

int main()
{
	std::ifstream f;
	f.open("untitled.msh");
	std::vector<Node> nodes;
	std::vector<Element> elements;
	Parser::parse(f, nodes, elements);
	std::vector<std::vector<double>> speeds;
	speeds.resize(3);
	//resize to dimension and fill
	for (auto el : elements)
	{
		//find neigbours
		//count flux in TVD

	}
	return 0;
}