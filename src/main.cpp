#include <iostream>
#include <fstream>
#include <algorithm>
#include <functional>
#include "headers/Point.hpp"
#include "headers/Parser.hpp"
#include "headers/ComputationalElement.hpp"

int main()
{
	std::ifstream f;
    f.open("temp.msh");
	std::vector<Node> nodes;
	std::vector<Element> elements;
	Parser::parse(f, nodes, elements);
	//resize to dimension and fill
	for (auto el : elements)
	{
		//find neigbours
		//count flux in TVD

	}
    std::vector<ComputationalElement> compElements(std::make_move_iterator(elements.begin()), std::make_move_iterator(elements.end()));
	return 0;
}
