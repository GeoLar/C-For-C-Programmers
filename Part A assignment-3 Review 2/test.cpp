#include <iostream>

#include "EdgeWeightedGraph.hpp"
#include "MinimumSpanningTree.hpp"


int main (void) {

	EdgeWeightedGraph G {"dataG.txt"};

  MinimumSpanningTree mst {G};
	auto temp = mst.edges();
	while (!temp.empty()) {
		auto e = temp.front();
		temp.pop();
		std::cout << e.toString() << " ";
	}
	std::cout << "\n" << std::endl;
	std::cout << mst.weight() << std::endl;

	return 0;
}
