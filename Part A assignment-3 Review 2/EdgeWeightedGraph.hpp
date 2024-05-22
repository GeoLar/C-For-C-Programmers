#ifndef __EDGEWEIGHTEDGRAPH_HPP__
#define __EDGEWEIGHTEDGRAPH_HPP__

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include "Edge.hpp"


class EdgeWeightedGraph {
private:
	int V_;   // the number of vertices in the graph
	int E_;         // the number of edges in the graph

	std::vector<std::vector<Edge>> adj_;

public:
	EdgeWeightedGraph(int V);
	EdgeWeightedGraph(const std::string& filename);

	inline int V() const {
		return V_;
	}
	inline int E() const {
		return E_;
	}

	void addEdge(Edge e);

	std::vector<Edge> adj(int v) const;
	std::vector<Edge> edges() const;

	std::string toString() const;
};


#endif // __EDGEWEIGHTEDGRAPH_HPP__
