#ifndef __MINIMUMSPANNINGTREE_HPP__
#define __MINIMUMSPANNINGTREE_HPP__

#include <functional>
#include <queue>
#include <vector>

#include "Edge.hpp"
#include "EdgeWeightedGraph.hpp"

class MinimumSpanningTree {
private:
	std::vector<bool> marked_;      // MST vertices
	std::queue<Edge> mst_;          // MST edges
	std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> pq_;

	double weight_;

	void visit_(const EdgeWeightedGraph&, int);

public:
	MinimumSpanningTree(const EdgeWeightedGraph&);
	MinimumSpanningTree(const MinimumSpanningTree&) = default;
	~MinimumSpanningTree() = default;
	MinimumSpanningTree& operator= (const MinimumSpanningTree&) = default;

	std::queue<Edge> edges() const {
		return mst_;
	}

	double weight() const {
		return weight_;
	}
};



#endif  // __MINIMUMSPANNINGTREE_HPP__
