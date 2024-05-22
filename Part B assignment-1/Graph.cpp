
#include <cstddef>
#include <ctime>
#include <iostream>
#include <vector>
#include <set>
#include <string>

#include "Graph.hpp"

Graph::Graph(std::size_t node_count):node_count_(node_count) {
	for (std::size_t id = 0; id < node_count_; id++) {
		graph_.push_back(Node(id));
	}
}

void Graph::print(std::ostream& os) {
	Graph& g = *this;
	for (std::size_t i = 0; i < g.NodeCount(); i++) {
		std::size_t n = i;
		const Node& node = g.FindNode(n);
		std::cout << node.name << ": ";

		int path_count = 0;
		for (auto path : node.paths) {
			if (path_count++ > 0)
				std::cout << ", ";
			os  << "(" << g.FindNode(path.other_node_id).name << "," << path.cost << ")";
		}

		std::cout << std::endl;
	}
}

// Overloaded << for the Graph class
std::ostream& operator<<(std::ostream& os, Graph& g) {
	for (std::size_t i = 0; i < g.NodeCount(); i++) {
		std::size_t n = i;
		const Node& node = g.FindNode(n);
		os << node.name << ": ";

		int path_count = 0;
		for (auto path : node.paths) {
			if (path_count++ > 0)
				os << ", ";
			os << "(" << g.FindNode(path.other_node_id).name << "," << path.cost << ")";
		}

		os << std::endl;
	}

	return os;
}


// Implements Dijkstra's shortest path algorithm to find the shortest path between the nodes 
std::vector<Node*> Graph::FindShortestPath(const std::size_t from_node, const std::size_t to_node) {
	std::vector <Node*> shortest_path;

	return shortest_path;
}
