#include "Graph.h"
#include <iterator>
#include <cstring>
#include <cctype>

using std::cout;
using std::endl;
using std::make_pair;

Graph::Graph(double den, int nodeNum, int minR, int maxR)
{
	srand(static_cast<unsigned int>(time(0)));			// seed the random number generator
	int numOfEdgesPerNode= static_cast<int>(den * static_cast<float>((nodeNum * (nodeNum - 1)) / 2)); // D = 2E/V*(V-1)
 // Create nodeNum nodes
	for (int i= 0; i < nodeNum; ++i) 
	{
		node  	newVertex;
		adjList.push_back(newVertex);	// add the number of nodes required
	}
// Connect vertices 
	for (int i= 0; i < nodeNum; ++i) 
	{
		std::set<int> duplicateChk;
		duplicateChk.insert(i);
		for (int j= 0; j < numOfEdgesPerNode; ++j) 
		{ 
			int randomVertex= rand() % nodeNum;	   // Pick a random vertex to connect 
			int randomRange= (rand() % maxR) + minR;
		// Make sure no duplications
			for (auto lstIt: adjList[i]) 
			{
				duplicateChk.insert(lstIt.first);
			}
			if (duplicateChk.end() == duplicateChk.find(randomVertex)) 
			{
				duplicateChk.insert(randomVertex);
			// Undirected connection
				adjList[i].push_back(make_pair(randomVertex, randomRange));		
				adjList[randomVertex].push_back(make_pair(i, randomRange));
			}
		}
	}
/*******************************************************/
// Generate the edge length randomly from the set interval
#if (1 == VERBOSE_GRPH)
	for (int i= 0, j= 0; i < adjList.size(); ++i, j= 0) 
	{
		cout << i << ":";
		for (auto lstIt: adjList[i]) 
		{
			std::cout << "->" << '(' << lstIt.first << ',' << lstIt.second << ')';
			++j;
		}
		cout << endl;
	}
// Another way to view it
	for (int i= 0, j= 0; i < adjList.size(); ++i, j= 0) 
	{
		cout << i << ":";
		for (auto lstIt: adjList[i]) 
		{
			std::cout << "->" << (lstIt.first);
		}
		cout << "\n   ";
		for (auto lstIt: adjList[i]) 
		{
			std::cout << "," << (lstIt.second);
		}
		cout << endl;
	}
#endif
}
// set names for vertices (numbers are still available)
// names should be the same count as the vertices count
// Returns false if Names count > nodeNum set earlier or if failed for any reason to initialize
bool Graph::set_vertices_names(std::vector<std::string> lstNames)
{
	if (lstNames.size() > adjList.size()) 
	{
		return false;
	}
	for (int i= 0; i < lstNames.size(); ++i) 
	{
		vxValues.push_back(lstNames[i]);
	}
	return true;
}

//Graph::Graph(const Graph& G)
//{
//	int i= 0;
//
//	for (auto& vecIt: G.adjList)
//	{
//		//node newVertex;
//		adjList.push_back(vecIt);
//		//for (node::iterator lstIt: vecIt)
//		//{
//		//	adjList[i++].insert;
//		//}
//	}
//	cout << "\nCpy: ";
//	for (auto& It : adjList)
//	{
//		for (auto& pIt: It)
//		{
//			cout << "(" << pIt.first << ", " << pIt.second << ")";
//		}
//		cout << endl;
//	}
//	cout << "\nCpyOrg: ";
//	for (auto& It : G.adjList)
//	{
//		for (auto& pIt: It)
//		{
//			cout << "(" << pIt.first << ", " << pIt.second << ")";
//		}
//		cout << endl;
//	}
//	//adjList= G.adjList;
//}

// Returns vertex number gived the node name or -1 if it was not found
int	Graph::get_node_num(std::string name)
{
	int number= 0;
	std::string tmp;
	std::transform(name.begin(), name.end(), name.begin(), 
				   [](unsigned char Ch) { return std::tolower(Ch); });
	for (auto vertex: vxValues)
	{
		std::transform(vertex.begin(), vertex.end(), vertex.begin(), 
					  [](unsigned char Ch) { return std::tolower(Ch); });
		if (name == vertex)
		{
			return number; 
		}
		++number;
	}
	return -1;	// not found! (404)
}

// Returns number of vertices in the given graph
int Graph::V(void)
{
	int numOfVertecis= 0;

	for (auto& It: adjList) 
	{
		++numOfVertecis;
	}
	return numOfVertecis;
}

// Returns number of Edges in the given graph
int Graph::E(void)
{
	if (0 == V()) 
	{
		return 0;
	}
	int numOfEdges= 0;
	for (auto VxIt: adjList) 
	{
		for (auto rangeIt: VxIt) // number of elements in each list is the number of edges
		{
			++numOfEdges;
		}
	}
	return numOfEdges;
}

// tests whether there is an edge from node x to node y
bool Graph::adjacent(int x, int y)
{
	if (0 == V()) 
	{
		return false;
	}
	for (auto lstIt: adjList[y]) 
	{
		if (lstIt.first == x) // first element in the pair is the vertex
		{
			return true;
		}
	}
	return false;
}

// Adds to G the edge from x to y, if it is not there.
// Returns false if there already an edge, true otherwise
bool Graph::add_edge(int x, int y, int weight)
{	
	if (0 == V()) 
	{
		return 0;
	}
	if (false == adjacent(x, y)) 
	{
		adjList[x].push_back(make_pair(y, weight));
		adjList[y].push_back(make_pair(x, weight));
		return true;
	}
	return false;
}

// Lists all nodes y such that there is an edge from x to y, 
// Returns the number of neighbor nodes or 0 if there is none
node& Graph::neighbors(int x)
{
	return adjList[x];	// reference to the x node contains the connected nodes and weights
}

// Lists all nodes y such that there is an edge from x to y using names.
// Returns the number of neighbor nodes or 0 if there is none.
node& Graph::neighbors(std::string vertexName)
{
	if (0 == vxValues.size())
	{
		node s;
		return s;
	}
	int vertex= get_node_num(vertexName);
	return adjList[vertex];
}

// Removes the edge from x to y, if it is there
// Returns true if succeded or false if there was no edge connecting both nodes
bool Graph::del_edge(int x, int y)
{
	if (false == adjacent(x, y)) 
	{
		return false;
	}
	for (auto VxIt= adjList[y].begin(); VxIt != adjList[y].end(); ++VxIt)
	{
		if (x == VxIt->first)
		{
			adjList[y].erase(VxIt);
		}
	}
	for (auto VxIt= adjList[x].begin(); VxIt != adjList[x].end(); ++VxIt)
	{
		if (x == VxIt->first)
		{
			adjList[x].erase(VxIt);
		}
	}
	return true;
}

// Returns the value associated to the edge (x,y)
int Graph::get_edge_value(int x, int y)
{
	if (true == adjacent(x, y)) 
	{
		for (auto lstIt: adjList[x]) 
		{
			if (y == lstIt.first) 
			{
				return lstIt.second;
			}
		}
	}
	return 0;
}

// Sets the value associated to the edge (x,y)
bool Graph::set_edge_value(int x, int y, int v)
{
	if (true == adjacent(x, y)) 
	{
		for (auto& lstIt: adjList[x]) 
		{
			if (y == lstIt.first) 
			{
				lstIt.second= v;
			}
		}
		for (auto& lstIt: adjList[y]) 
		{
			if (x == lstIt.first) 
			{
				lstIt.second= v;
			}
		}
		return true;
	}
	return false;
}

// Returns the value associated with the node x.
std::string Graph::get_node_value(int x)
{
	return vxValues[x];
}

// Sets the value associated with the node x to a
void Graph::set_node_value(int x, std::string a)
{
	vxValues[x]= a;
}

// Prints the whole graph with its weights in two formats
void Graph::display(valueMode modeName)
{
	cout << "\n\n";
	if (number == modeName)
	{
		for (int i= 0, j= 0; i < adjList.size(); ++i, j= 0) 
		{
			cout << i << ":";
			for (auto lstIt: adjList[i]) 
			{
				std::cout << "->" << '(' << lstIt.first << ',' << lstIt.second << ')';
				++j;
			}
			cout << endl;
		}
// Another way to view it
		//cout << "\n\n";
		//for (int i= 0, j= 0; i < adjList.size(); ++i, j= 0) 
		//{
		//	cout << i << ":";
		//	for (auto lstIt: adjList[i]) 
		//	{
		//		std::cout << "->" << (lstIt.first);
		//	}
		//	cout << "\n";
		//	for (auto lstIt: adjList[i]) 
		//	{
		//		std::cout << "," << (lstIt.second);
		//	}
		//	cout << endl;
		//}
	}
	else
	{
		if (0 == vxValues.size())	// if no names assigned return
		{
			return;
		}
		for (int i= 0, j= 0; i < adjList.size(); ++i, j= 0) 
		{
			cout << vxValues[i] << ":";
			for (auto lstIt: adjList[i]) 
			{
				std::cout << "->" << '(' << vxValues[lstIt.first] << ',' << lstIt.second << ')';
				++j;
			}
			cout << endl;
		}
// Another way to view it
		cout << "\n\n"; 
		for (int i= 0, j= 0; i < adjList.size(); ++i, j= 0) 
		{
			cout << vxValues[i] << ":";
			for (auto lstIt: adjList[i]) 
			{
				std::cout << "->" << (vxValues[lstIt.first]);
			}
			cout << "\n";
			for (auto lstIt: adjList[i]) 
			{
				std::cout << "," << (lstIt.second);
			}
			cout << endl;
		}		
	}
}

// Displays a one node in two formats
void Graph::display_node(const node& disp, valueMode modeName)
{
	cout << "\nNode\n";
	if (name == modeName)
	{
		//cout << vxValues.size();
		if (0 == vxValues.size())	// if no names assigned return
		{
			return;
		}
		for (auto& lstIt: disp) 
		{
			std::cout << "->" << '(' << vxValues[lstIt.first] << ',' << lstIt.second << ')';
		}
		cout << "\n\n";
	// Another way to view it
		cout << vxValues[(disp.begin())->first] << ":";
		for (auto lstIt: disp) 
		{
			std::cout << "->" << (vxValues[lstIt.first]);
		}
		cout << "\n";
		for (auto lstIt: disp) 
		{
			std::cout << "," << (lstIt.second);
		}
	}
	else 
	{
		for (auto lstIt: disp) 
		{
			std::cout << "->" << '(' << lstIt.first << ',' << lstIt.second << ')';
		}
		//cout << "\n\n";
	// Another way to view it
		//for (auto lstIt: disp) 
		//{
		//	std::cout << "->" << (lstIt.first);
		//}
		//cout << "\n";
		//for (auto lstIt: disp) 
		//{
		//	std::cout << "," << (lstIt.second);
		//}
	}
	cout << endl;
}
