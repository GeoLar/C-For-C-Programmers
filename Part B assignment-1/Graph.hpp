#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <cstddef>
#include <iostream>
#include <vector>
#include <set>
#include <string>


// Class for a node in the graph and the paths it has connected
// with other nodes in the graph.
//
// Paths between nodes are impletended in a multiset (list). I choosed
// this solution because I think the implementation will be more
// readable and easier to understand.
//
class Node {
public:
	// Inner class for an edge to another node (vertice)
	class Path {
	public:
		const std::size_t other_node_id; // Id of the node at the other end of the path
		const double cost; // The cost (distanc) for this path

		// Constructor
		Path(std::size_t id, double cost) :other_node_id(id), cost(cost) {
		}

		// Overload of the less than operator.
		// A node path is stored in a set and should be sorted ascending according to the path cost
		bool operator<(const Path& rhs) const {
			return (this->cost < rhs.cost);
		}
	};

	const std::size_t node_id; // Id of the node, same as the index of the node in the graphs vector of nodes
	std::string name; // Used in printouts of the graph to get a more readable output
	std::multiset<Node::Path> paths; // Container of the paths to other nodes. Sorted ascending on path cost

	//Constructor
	Node(std::size_t id) :node_id(id), paths(), name(std::to_string(id)) {
	}

	inline void AppendPath(Path path) {
		paths.insert(path);
	}

	inline void AppendPath(std::size_t to_node, double cost) {
		paths.insert(Path(to_node, cost));
	}
};

// Simple implmentation of a graph. The nodes in the graph are static after creation but
// the paths between them may be removed and new one created by the InitGraph method.
class Graph {
public:
	// Constructors
	Graph() : Graph(0) {
	}

	Graph(std::size_t node_count);

	// Lookup a node in the graph, returns a reference to the node that matches the node id. 
	inline Node& FindNode(std::size_t node_id) {
		return graph_[node_id];
	}

	// Returns number of nodes in the graph
	inline std::size_t NodeCount() const {
		return(node_count_);
	}

	// Returns the shortest path between the nodes in the graph or an empty vector if no such path exists  
	std::vector<Node*> FindShortestPath(const std::size_t from_node, const std::size_t to_node);

	friend std::ostream& operator<< (std::ostream& os, const Graph& g);

	virtual void print(std::ostream& os);

protected:
	std::size_t node_count_; //Number of nodes in the graph
	std::vector<Node> graph_; // Container of all nodes and all paths between them
};

#endif //GRAPH_HPP 
