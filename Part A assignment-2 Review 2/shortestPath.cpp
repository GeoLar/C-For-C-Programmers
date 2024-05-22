#include "shortestPath.h"
#include <algorithm>
#include <iterator>

using std::pair;
using std::make_pair;

// Find shortest path between u-w and returns the sequence of vertices representing shorest path u-v1-v2-…-vn-w.
// First element of the pair is the cost/value, second is the node number
std::vector<int>& shPath::path(int source, int dest)
{
	using std::cout;
	using std::endl;
	decltype(graph.V()) numOfV= graph.V();	// number of vertices
	decltype(graph.V()) currNode;
// A vector representing each node
// First element represents previous connected node in the shortest path
// Second is the cost of the path up to this node (sPath[i])
	std::vector<pair<int, int>> sPath;	// sPath(PreviousNode, cost), index of a vector is the vertix name
	//prioQDuel clsSet;			// opnSet(cost, node), clsSet(cost, node)
	std::vector<int> opnSet;
	node clsSet;
// Initialization	
	for (currNode= 0; currNode < numOfV; ++currNode)
	{
		sPath.push_back(make_pair(-1, INT_MAX / 2));	// All paths are intially infinity
	}
	currNode= source;		 // start from the source vertex
	opnSet.push_back(source);
	sPath[source].second= 0; // Distance from source to source
	for (int i= 0; i < numOfV; ++i)
	{	// while all vertices has not been visited yet
		bool found= true;
		clsSet= graph.neighbors(currNode);	// neighbors to the current new vertix
		for (auto& vxIt: clsSet) // vxIt.first (node), vxIt.second (edge/cost/value)
		{ 
			found= (std::find(opnSet.begin(), opnSet.end(), vxIt.first) !=  opnSet.end());
			if (true == found)
			{
				continue;
			}
			if (sPath[vxIt.first].second > vxIt.second + sPath[currNode].second)	// if the new cost less than the existing
			{
				sPath[vxIt.first].second= vxIt.second + sPath[currNode].second;		// save the new less cost
				sPath[vxIt.first].first=   currNode;	// save the previous node to this new cost
			}
 		}
		int vertexIndex= 0;	// number of the vertix is its name 
		for (auto& sPathIt: sPath) // check every node if it is in the closed set
		{
			if (-1 == sPathIt.first) // If it is not connected to the source(eventually), skip it
			{
				continue;
			}
			found= (std::find(opnSet.begin(), opnSet.end(), vertexIndex) != opnSet.end());
			if (false == found)
			{
				opnSet.push_back(vertexIndex); // mark as visited
				currNode= vertexIndex;
				break;
			}
			++vertexIndex;	
		}
	}
	static std::vector<int> shortestPath;
	if (-1 == sPath[dest].first) // if there is no path to the destination vertix return (INT_MAX, INT_MAX)
	{
		cout << "\nNo Path existed!\n";
		shortestPath.push_back(INT_MAX);
		sPathCost= 0;
	}
	else
	{
		currNode= source;
		for (int vertix= dest; vertix != source; ++currNode)
		{
			shortestPath.push_back(vertix);
			vertix= sPath[vertix].first; // next connected shortest path vertix
		}
		shortestPath.push_back(source);
		sPathCost= sPath[dest].second;
	}
	graph.display(Graph::valueMode::number);
	return shortestPath;
}

// Return the path cost associated with the shortest path.
int shPath::path_cost(void)
{
	return sPathCost;
}
