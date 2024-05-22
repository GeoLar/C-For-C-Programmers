//
// Course C++ for C-programmers Part A. Homework 3.
// Implementation of MST algorithm.
//
// The program implements a simple graph and calculates theminimal
// spanning tree (MST) between the modes of the graph.
//
#include <cstddef>
#include <ctime>
#include <fstream>
#include <iostream>
#include <iterator>
#include <random>
#include <set>
#include <sstream>
#include <string>
#include <vector>


// Class for a node in the graph and the paths it has connected
// with other nodes in the graph.
class Node {
public:
	// Inner class for an edge to another node
	class Path {
	public:
		const std::size_t other_node_id; // Id of the node at the other end of the path
		const double cost; // The cost (distanc) for this path

		// Constructor
		Path(std::size_t id, double cost) :other_node_id(id), cost(cost) {
		}

		// Overload of the less than operator.
		// A node path is stored in a set and should be sorted descending according to the path cost
		bool operator>(const Path& rhs) const {
			return (this->cost > rhs.cost);
		}

		// Overload of the less than operator.
		// A node path is stored in a set and should be sorted ascending according to the path cost
		bool operator<(const Path& rhs) const {
			return (this->cost < rhs.cost);
		}
	};

	std::size_t node_id; // Id of the node, same as the index of the node in the graphs vector of nodes
	std::string name; // Used in printouts of the graph to get a more readable output
	std::multiset<Node::Path> paths; // Container of the paths to other nodes. Sorted ascending on path cost

	//Constructor
	Node(std::size_t id) :node_id(id), name(std::to_string(id)), paths() {
	}
};

// Simple implmentation of a graph. The nodes in the graph are static after creation but
// the paths between them may be removed and new one created by the InitGraph method.
class Graph {
public:
	// Constructors
	Graph(std::size_t node_count):node_count_(node_count) {
	}

	// Load graph from datafile
	Graph(const std::string& filepath);

	// Lookups the nodes in the graph and returns a reference to the node that matches the node id. 
	inline const Node& FindNode(std::size_t node_id)  {
		return graph_[node_id];
	}

	// Returns number of nodes in the graph
	inline std::size_t NodeCount() {
		return(node_count_);
	}

	friend std::ostream& operator<< (std::ostream& os, const Graph& g);

private:
	std::vector<Node> graph_; // Container of all nodes and all paths between them
	std::size_t node_count_;
};

// Constructor, loads the graph content from file
Graph::Graph(const std::string& filepath):node_count_(0) {
	std::ifstream df;
	std::string line;

	df.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	df.open(filepath, std::iostream::in);
	if (df.fail ())
		return;
		
	if (!df.eof()) {
		std::getline(df, line);
		std::istringstream ss(line, std::istringstream::in);
		ss >> node_count_; // Read number of nodes in the graph
	}
	graph_ = std::vector<Node>(node_count_, Node(-1));

	// Load node and path data
	while (!df.eof()) {
		std::getline(df, line);
		std::istringstream ss(line, std::istringstream::in);
		std::vector<std::string> words;

		while (!ss.eof()) {
			std::string v;
			ss >> v;
			words.push_back(v);
		}

		int i = (words.size() == 3 ? 0 : 1);
		std::string name = words[0];
		int node1 = std::stoi(words[i++]);
	    int node2 = std::stoi(words[i++]);
		int cost = std::stoi(words[i++]);
		
		ss >> node1 >> node2 >> cost;

		Node& n1 = graph_[node1];
		if (n1.node_id == -1) n1.node_id = node1;
		n1.name = name;
		n1.paths.insert(Node::Path(node2, cost));
	}

	df.close();
}

// Overloaded << for the Graph class
std::ostream& operator<<(std::ostream& os, Graph& g) {
	for (int i = 0; i < g.NodeCount(); i++) {
		std::size_t n = i;
		const Node node = g.FindNode(n);
		os << node.name<< ": ";

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

// Implements the Jarnik-Prim algorithm to find MST (Minimum Spanning Tree) of the graph.
class MinimumSpanningTree {
public:
	// CVontainer for the computed MST
	class MST {
	public:
		double cost; // The cost for the MST
		std::vector<std::pair<std::size_t, double>> tree; // Container of the MST
	};

	bool debug;

	MinimumSpanningTree(Graph& graph):graph_(graph), debug(false) {};

	void JarnikPrimMST(MST& mst, unsigned  from_node_id);

private:
	Graph& graph_;
};


// Helper class to lookup closed_set by node id in method JarnikPrimMST
class MstNodeEqual {
public:
	MstNodeEqual(std::size_t id):id (id) {}

	bool operator () (const std::pair<std::size_t, double>& rhs) const{
		return id == rhs.first;
	}

private:
	std::size_t id;
};

// Implementation of the Jarnik-Prime's algorithm to find a MST for the graph.
void MinimumSpanningTree::JarnikPrimMST(MST& mst, unsigned from_node_id) {
	std::set<std::pair<double, std::size_t>> open_set; // Nodes to be evaluated, sorted ascending by node cost.

	// Loop through nodes in the graph until thera are no more to evaluate
	open_set.insert(std::make_pair (0, from_node_id)); // 0 cost for the node we start from
	while (!open_set.empty()) {
		// Get the node with the lowest cost from the open set
//		auto current_itr = --open_set.end();
		auto current_itr = open_set.begin();
		std::size_t  current_node_id = (*current_itr).second; // Node id

		// Evalute the nodes paths if the node not already has been evaluated
		auto mst_lookup_itr = std::find_if(mst.tree.begin(), mst.tree.end(), MstNodeEqual(current_node_id));
		if (mst_lookup_itr == mst.tree.end ()) {
			const Node current_node = graph_.FindNode((*current_itr).second);
			const double current_node_cost = (*current_itr).first;

			// Put reacable nodes not already evaluated into the open set.
			mst.tree.push_back(std::make_pair(current_node.node_id, current_node_cost));
			for (auto path_itr = current_node.paths.begin(); path_itr != current_node.paths.end(); path_itr++) {
				Node::Path path = *path_itr;
				auto mst_lookup_itr = std::find_if(mst.tree.begin(), mst.tree.end(), MstNodeEqual(path.other_node_id));
				if (mst_lookup_itr == mst.tree.end()) {
					open_set.insert(std::make_pair(path.cost, path.other_node_id));
				}
			}
		}

		open_set.erase(current_itr);
	}

	// Calculate the MST cost
	mst.cost = 0;
	for (auto ni = mst.tree.begin(); ni != mst.tree.end(); ni++) { 
		double node_cost = (*ni).second;
		mst.cost += node_cost;
	}
}

// Simple class to run tests.
class Test {
public:
	// Runs all test cases
	void run() {
		Graph ga("t.dat");
		ShortestPathTest(ga, 0, true);
		
		// This is the assigment of the homwwork
		Graph g("graph-homework-3.dat");
    	ShortestPathTest(g, 0, true);

		// MST for the graphs presented in lesson 4.2 and 4.3
		Graph g42("graph-lesson-4-2.dat");
		ShortestPathTest(g42, 0, true);

		Graph g43("graph-lesson-4-3.dat");
		ShortestPathTest(g43, 0, true);
		
	}

private:
	// Executes one test case 
	void ShortestPathTest(Graph& graph, unsigned node_id, bool debug) {
		std::cout << "Test case using " << graph.NodeCount() << " nodes" << std::endl;

		if (debug) {
			std::cout << "Graph data:" << std::endl;
			std::cout << graph << std::endl;
		}

		// Calculate MST and print the result
		MinimumSpanningTree sp(graph);
		sp.debug = debug;

		MinimumSpanningTree::MST mst;
		sp.JarnikPrimMST(mst, node_id);
		if (mst.cost >= 0) {
			std::cout << "MST Cost: " << mst.cost << " MST: ";
			int i = 0;
			for (auto n : mst.tree) {
				std::cout << (i++ > 0 ? "-" : "") << graph.FindNode(n.first).name;
			}
		} else {
			std::cout << "The graph is disconnected";
		}
		std::cout << std::endl << std::endl;
	}
};

// Run tests and terminate
int main() {
	Test().run();
	return(0);
}
