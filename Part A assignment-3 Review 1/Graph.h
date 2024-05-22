#include <iostream>
#include <string>
#include <vector>

typedef std::vector <int> listOfEdges;

namespace Assignment {
	class Graph {
	public:
		Graph() :
			V(0),
			E(0),
			adjacencyList(std::vector<listOfEdges>(V)) {
		}

		Graph(int V);
		Graph(const std::string& filename);

	private:
		std::vector <listOfEdges> adjacencyList;
		int V;
		int E;
	};
}
