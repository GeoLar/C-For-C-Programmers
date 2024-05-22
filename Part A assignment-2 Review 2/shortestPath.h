#ifndef _SHORTESTPATH_H_
#define _SHORTESTPATH_H_

#include <iostream>
#include "Graph.h"

using pathType= std::vector<std::pair<int, int>>;

class shPath
{
	pathType shPathGraph;
	Graph graph;
	int sPathCost;
public:
	shPath(Graph& usermap): graph(usermap), sPathCost(0) { }
	~shPath() { }
// Find shortest path between u-w and returns the sequence of vertices representing shorest path u-v1-v2-…-vn-w.
	std::vector<int>& path(int source, int dest); 
// Return the path cost associated with the shortest path.
	int path_cost(void); 
};

#endif