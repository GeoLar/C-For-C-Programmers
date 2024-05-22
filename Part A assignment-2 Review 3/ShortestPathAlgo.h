#ifndef SHORTESTPATHALGO
#define SHORTESTPATHALGO

#include "graph.h"
#include <iostream>
#include "PriorityQueue.h"
#include <vector>
#include <algorithm>
#include "node.h"
#include "Supporting_fns.h"


#define MIN_DISTANCE 10
#define MAX_DISTANCE 100

class ShortestPathAlgo
{
private:
	graph g;
	PriorityQueue unvisited_set;	
	vector<int32> distances;
	vector<int32> Shortest_path_list;
	vector<int32> nodes_parents;
	uint32 distance_travelled;
	bool simulation_result;
	uint32 current_node;
	uint32 initial_node;
	uint32 target_node;
	uint32 gen_density;
	
public:

	//Class constructor, define and initialize needed data structures.
	ShortestPathAlgo(uint8 simulation_size, uint32 gen_density, uint32 initial_node, uint32 target_node);
	
	//Run simulation, returns true if target node was reached, flase if no path exists to target node.
	bool run_simulation(void);
	
	//Returns the distance travelled if the target node was reached.
	uint32 get_distance_travelled(void);

	

};



#endif