//
// Course C++ for C-programmers Part A. Assigment 2.
// Implementation of Dijksta's shortest path algorithm.
//
// The program implements a simple graph and calculates the shortest path
// between the graphs nodes using Dijkstra's shortest path algorthm.
//
#include <cstddef>
#include <ctime>
#include <iostream>
#include <random>
#include <vector>
#include <set>


// Class for a node in the graph and the paths it has connected
// with other nodes in the graph.
//
// Paths between nodes are impletended in a multiset (list). I choosed
// this solution because I think the implementation will be more
// readable and easier to understand.
//
// All properties are readonly, nothing will change after an instance
// of a Node has been created.
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
	std::multiset<Node::Path> paths; // Container of the paths to other nodes. Sorted ascending on path cost

	//Constructor
	Node(std::size_t id) :node_id(id), paths() {
	}
};

// Simple implmentation of a graph. The nodes in the graph are static after creation but
// the paths between them may be removed and new one created by the InitGraph method.
class Graph {
public:
	const std::size_t kNodeCount; //Number of nodes in the graph

	// Constructors
	Graph(std::size_t node_count): Graph(node_count, std::time(0)) {
	}

	Graph(std::size_t node_count, long unsigned seed);

	// Initializes a graph of kNodeCount nodes with randomly generated paths and path costs.
	void InitGraph(const double density, const unsigned min_distance, const unsigned max_distance);

	// Lookups the nodes in the graph and returns a reference to the node that matches the node id. 
	inline const Node& FindNode(std::size_t node_id) {
		return graph_[node_id];
	}

private:
	std::default_random_engine randome_engine_; // Used to random generate paths (edges) between nodes  
	std::seed_seq seed_; // Used by random_engine_ to generate sequemces of pseudo random numbers
	std::vector<Node> graph_; // Container of all nodes and all paths between them
};

// Constructor initalizing the random generator and allocating nodes for the graph.
Graph::Graph(std::size_t node_count, long unsigned seed):kNodeCount(node_count), seed_({ seed }) {
	// Initialize random generator
	randome_engine_ = std::default_random_engine(seed_);

	// Create all nodes in the graph, a nodes id is the same as the index in the vector
	for (int id = 0; id < kNodeCount; id++) {
		graph_.push_back(Node(id));
	}
}

// Implementation of method to randomly generate paths between nodes.
void Graph::InitGraph(const double density, const unsigned min_cost, const unsigned max_cost) {
	// Parameter sanity check 
	if ((density <= 0) || (density > 1)) {
		std::cerr << "Bad value for density: " << density << ". Should be > 0.0 and <= 1.0" << std::endl;
		return;
	}

	if (min_cost == 0) {
		std::cerr << "min_cost should be greater than 0 " << std::endl;
		return;
	}

	// Create needed random number generators
	std::uniform_real_distribution<double> random_density(0.0, 1.0);
	std::uniform_int_distribution<int> random_cost(min_cost, max_cost);

	// Reset existing paths between nodes
	for (std::size_t i = 0; i < graph_.size(); i++) {
		graph_[i].paths.clear();
	}

	// Loop through all nodes and create path between them according to
	// the given desnsity and cost limits.
	for (std::size_t i1 = 0; i1 < Graph::kNodeCount; i1++) {
		for (std::size_t i2 = i1+1; i2 < Graph::kNodeCount; i2++) {
			double p = random_density(randome_engine_); // Random number to keep the number of paths to the wished density
			int cost = random_cost(randome_engine_); // Random cost

			// Create a path between the nodes if p is below the path density of the graph
			if (p < density) {
				Node& node1 = graph_[i1];
				Node& node2 = graph_[i2];

				node1.paths.insert(Node::Path(i2, cost));
				node2.paths.insert(Node::Path(i1, cost));
			}
		}
	}
}

// Implements Djikstra's algorithm to find the shortest path between nodes in a graph
class ShortestPath {
public:
	bool debug;

	ShortestPath(Graph& graph) :graph_(graph), debug(false) {};

	double DijkstraShortestPath(unsigned  from_node_id);

private:
	Graph& graph_;
};


// Helper class to lookup closed_set by node id in method DijkstraShortestPath
class ClosedSetNodeIdEqual {
public:
	ClosedSetNodeIdEqual(std::size_t id):id (id) {}

	bool operator () (const std::pair<double, std::size_t>& rhs) const{
		return id == rhs.first;
	}

private:
	std::size_t id;
};

// Helper class to lookup open_set by node id in method DijkstraShortestPath
class OpenSetNodeIdEqual {
public:
	OpenSetNodeIdEqual(std::size_t id) :id(id) {}

	bool operator () (const std::pair<double, std::size_t>& rhs) const {
		return id == rhs.second;
	}

private:
	std::size_t id;
};

// Implementation of Dijksta's shortest path algorithm.
double ShortestPath::DijkstraShortestPath(unsigned from_node_id) {
	std::set<std::pair<double, std::size_t>> open_set; // Nodes to be evaluated, sorted ascending by node cost.
	std::set<std::pair<std::size_t, double>> closed_set; // Evaluated nodes, sorted ascending by node id.

	// Loop implementing Dijkstra's shortest path algorithm. The open_set contains the nodes left to
	// evaluate. Start with the source node. 
	open_set.insert(std::make_pair (0, from_node_id)); // 0 cost for the source node
	while (!open_set.empty()) {
		// Get the node with the lowest cost from the open set
		auto current_itr = open_set.begin();
		const Node current_node = graph_.FindNode((*current_itr).second);
		const double current_node_cost = (*current_itr).first;

		// Move the node to the closed set. Need to swap position of first and second
		closed_set.insert(std::make_pair(current_node.node_id, current_node_cost));
		open_set.erase(current_itr);

		// Evaluate all of the node paths.The nodes paths are sorted ascending
		// according to the path cost and a path are retrieved by evaluating the not
		// yet evaluated path having the lowest cost.
		for (auto path_itr = current_node.paths.begin(); path_itr != current_node.paths.end(); path_itr++) {
			Node::Path path = *path_itr;

			// Evaluate the other node cost only if the other end not exists the closed_set. 
			auto closed_lookup_itr = std::find_if(closed_set.begin(), closed_set.end(), ClosedSetNodeIdEqual (path.other_node_id));
			if (closed_lookup_itr == closed_set.end()) {
				// Calculate the cost for the other node
				double other_node_cost = current_node_cost + path.cost;

				// Update/insert the other node cost. If itshould be replaced.
				auto open_itr = std::find_if(open_set.begin(), open_set.end(), OpenSetNodeIdEqual(path.other_node_id));
				if (open_itr == open_set.end()) {
					// Add the other node to the open set to have it's paths evaluated.
					open_set.insert(std::make_pair(other_node_cost, path.other_node_id));
				} else if ((open_itr != open_set.end()) && (other_node_cost < (*open_itr).first)) {
					// Replace the existing cost with the new lower cost.
					open_set.erase(open_itr);
					open_set.insert(std::make_pair(other_node_cost, path.other_node_id));
				}
			}
		}
	}

	// Calculate the average cost for all of the nodes reachable from the source node (from_node_id)
	double sum_cost(0);
	unsigned node_count(0);
	for (auto ni = closed_set.begin(); ni != closed_set.end(); ni++) { 
		double node_cost = (*ni).second;
		if ((*ni).first != from_node_id) {
			node_count++;
			sum_cost += node_cost;

			if (debug) {
				// Print out the shortest path cost for the node
				std::cout << (*ni).first << " " << (*ni).second << std::endl;
			}
		}
	}
	double average_cost =  (node_count > 0? (sum_cost / node_count) : -1);

	return (average_cost);
}

// Simple class to run tests to verify implementaion of Dijkstas shortest path algorithm.
class Test {
public:
	// Runs all test cases
	void run() {
		// Test case with few nodes where nodes, path and results are printed
		Graph g(10);
		ShortestPathTest(g, 0, 0.2, 1, 10, true);

		// Test cases to accomplish the assigment
		Graph graph(50, std::time (0));
		ShortestPathTest(graph, 0, 0.2, 1, 10, false);
		ShortestPathTest(graph, 0, 0.4, 1, 10, false);
	}

private:
	// Executes one test case 
	void ShortestPathTest(Graph& graph, unsigned node_id, double density, unsigned min_cost, unsigned max_cost, bool debug) {
		std::cout << "Test case using " << graph.kNodeCount << " nodes" 
			<< ", density: " << density << ", min cost: " << min_cost << ", max cost: " << max_cost 
			<< ", debus is " << (debug ? "on" : "off")
			<< std::endl;


		// Create the paths between nodes in the graph
		graph.InitGraph(density, 1, 10);

		if (debug) {
			// Print all nodes and paths between them
			for (auto i = 0; i < graph.kNodeCount; i++) {
				Node node = graph.FindNode(i);

				std::cout << (i < 10 ? "" : " ") << i << " ";
				for (std::multiset<Node::Path>::iterator pi = node.paths.begin(); pi != node.paths.end(); ++pi) {
					std::cout << (pi != node.paths.begin() ? ", " : "") << "{" << (*pi).other_node_id << "," << (*pi).cost << "}";
				}
				std::cout << std::endl;
			}
			std::cout << std::endl;
		}

		// Calculate shortest paath to other nodes in the graph and print the result
		ShortestPath sp(graph);
		sp.debug = debug;

		double average_cost = sp.DijkstraShortestPath(node_id);
		if (average_cost >= 0) {
			std::cout << " Average cost from node " << node_id << " is " << average_cost;
		} else {
			std::cout << " There are no paths from node " << node_id;
		}
		std::cout << std::endl << std::endl;
	}
};

// Run tests and terminate
int main() {
	Test().run();
	return(0);
}


/*
Printout from program

Test case using 10 nodes, density: 0.2, min cost: 1, max cost: 10, debus is on
0 {5,9}
1
2
3 {4,3}, {6,3}
4 {3,3}
5 {0,9}
6 {3,3}
7 {8,6}
8 {7,6}
9

5 9
 Average cost from node 0 is 9

Test case using 50 nodes, density: 0.2, min cost: 1, max cost: 10, debus is off
 Average cost from node 0 is 6.36735

Test case using 50 nodes, density: 0.4, min cost: 1, max cost: 10, debus is off
 Average cost from node 0 is 3.22449

*/

/*
What I learned
●	Apply and follow organisation coding standard
●	Use C++ reference online is a must
●	C++ is a much bigger language  than C
●	Not easy to know when to use pointer   (int*) or  reference  (int&)
●	Initializing std::vector, std::set was hard  to  learn
●	Use of auto  declaration makes  code more  readable
●	Classes are excellent to encapsulate code
●	Classes makes programming OO code easy.
●	There exists many different ways to build solutions in C++ due to it' s extensibility
●	Important to comment code since it can be hard to understand how a specific use of a class act. Explain whats going on so the reader can catch up. Important for one self also because one forgets why one did "this part of The code" this way.
●	C++ has loads of classes that already implements what you need  and want.

*/
