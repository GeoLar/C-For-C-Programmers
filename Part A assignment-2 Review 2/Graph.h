#ifndef GRAPH_H_
#define GRAPH_H_

#include <iostream>
#include <list>
#include <set>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

#define VERBOSE_GRPH		(0u)


// Implements a random intialized adjacency list using undirected Edge Lists
// Positive cost distances
using node= std::list<std::pair<int, int>>;

class Graph 
{
// A vector that contains sets repersenting the weight of the ranges of a vertix & list to represent both E & V of a node
	std::vector<node>   	    adjList;	// adjacency list
	std::vector<std::string>   vxValues;	// names for nodes 
public:	
	enum valueMode {name, number};
	Graph() { }	 // Default Constructor
// Creating a randomly initialized Graph using den as density, number of nodes and minR & maxR as the range 
	Graph(double den, int nodeNum, int minR, int maxR);	
// Graph(const Graph&);
	~Graph() noexcept { } // Vector get deleted automatically when it reaches end of the scope 
// Class methods
	// set names for vertices (numbers are still available)
	// names should be the same count as the vertices count
	// Returns false if Names count > nodeNum set earlier or if failed for any reason to initialize
	bool set_vertices_names(std::vector<std::string> lstNames);
	int V(void); // Returns number of vertices in the given graph
	int E(void); // Returns number of Edges in the given graph
	bool adjacent(int x, int y); // tests whether there is an edge from node x to node y.
// Lists all nodes y such that there is an edge from x to y. 
// Returns the number of neighbor nodes or 0 if there is none.
	node& neighbors(int x);		
// Lists all nodes y such that there is an edge from x to y using names.
// Returns the number of neighbor nodes or 0 if there is none.
	node& neighbors(std::string vertexName);	
// Removes the edge from x to y, if it is there
// Returns 1 if succeded or 0 if there was no edge connecting both nodes
	bool del_edge(int x, int y); 
// Adds to G the edge from x to y, if it is not there.
// Returns false if there already an edge, true otherwise
	bool add_edge(int x, int y, int weight);
// Returns the value associated with the node x.
	std::string get_node_value(int x);
// Sets the value associated with the node x to a
	void set_node_value(int x, std::string name);
// Returns vertex number gived the node name or -1 if it was not found
	int	get_node_num(std::string name);
// Returns the value associated to the edge (x,y)
	int get_edge_value(int x, int y);
// Sets the value associated to the edge (x,y)
	bool set_edge_value(int x, int y, int v);
// Prints the whole graph with its weights in two formats
// Second, sets the vertices to be displayed by their values or numbers
	void display(valueMode modeName);	
// Displays a one node in two formats
// Second, sets the node to be displayed by its valuee or number
	void display_node(const node& disp, valueMode modeName);
};
#endif