#include <iostream>
#include <iterator>
#include "Graph.h"
#include "shortestPath.h"

const int nodeNum= 11;
std::vector<std::string> nodeNames= 
{
	"Cairo", "Alexandria", "Assuit", "Damietta",
	"Sharqia", "Port said", "Sharm El-sheikh", "Marsa allam",
	"Dahab", "Giza", "Sina"
};

int main(void)
{
	using std::pair;
	using std::make_pair;
	Graph G(0.1f, nodeNum, 3, 15);
	shPath sp(G);

	std::cout << "\nset_vertices_names: "  	 << G.set_vertices_names(nodeNames);
	std::cout << "\nNumber of Edges: "    	 << G.E();
	std::cout << "\nNumber of Vertices: " 	 << G.V();
	std::cout << "\nget_edge_value(0, 5): "  << G.get_edge_value(2, 9);
	std::cout << "\nAdjacent(0, 5): "    	 << G.adjacent(0, 5);
	std::cout << "\nget_edge_value(0, 5): "  << G.get_edge_value(0, 5);
	std::cout << "\nAdd_edge(0, 5, 9): "  	 << G.add_edge(0, 5, 9);
	std::cout << "\nget_node_num(Cairo): "   << G.get_node_num("Cairo");
	std::cout << "\nget_node_num(Dahab): "   << G.get_node_num("Dahab");
	std::cout << "\nget_node_num(Arish): "   << G.get_node_num("Arish");
	std::cout << "\nget_node_num(SiNA): "  	 << G.get_node_num("SiNA");
	std::cout << "\nget_node_num(SharQia): " << G.get_node_num("SharQia");
	std::cout << "\nset_edge_value(0, 5, 10): "  << G.set_edge_value(0, 5, 10);
	G.display(Graph::valueMode::number);
	std::cout << std::endl;
	std::cout << "\nget_edge_value(0, 5): "  << G.get_edge_value(0, 5);
	G.display_node(G.neighbors(0), Graph::valueMode::number);
	G.display_node(G.neighbors("Giza"), Graph::valueMode::name);

	std::vector<int> sPath= sp.path(0, 10);
	std::cout << "Shortest Path: ";
	std::copy(sPath.rbegin(), sPath.rend(), std::ostream_iterator<int, char>(std::cout, " "));
	std::cout << "\nShortest path cost: " << sp.path_cost() << std::endl;

	return 0;
}

