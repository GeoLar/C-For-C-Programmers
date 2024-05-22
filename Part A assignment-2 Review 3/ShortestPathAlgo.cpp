#include "ShortestPathAlgo.h"
#include "types.h"
using namespace std;

ShortestPathAlgo::ShortestPathAlgo(uint8 simulation_size, uint32 gen_density, uint32 initial_node, uint32 target_node)
	:   g(simulation_size), 
		distances(simulation_size), 
		nodes_parents(simulation_size, UNDEFINED),
		distance_travelled(0),
		simulation_result(true),
		initial_node(initial_node),
		target_node(target_node),
		current_node(initial_node),
		gen_density(gen_density)
{}


bool ShortestPathAlgo::run_simulation(void)
{
	//Generate graph edges.
	g.generate(gen_density, MIN_DISTANCE, MAX_DISTANCE);
	if(VERBOSE)	g.print();
	
	//Populate the initial node set priority queue and distances to infinity, expect for initial node(set to zero)
	for(uint8 i=0;i<g.V();i++)
	{
		if(i==initial_node)
		{
			unvisited_set.insert(node(initial_node, 0));
			distances[initial_node] = 0;
		}
		else
		{
			unvisited_set.insert(node(i, INFINITY_VALUE));
			distances[i] = INFINITY_VALUE;
		}
	}

	//Loop over all nodes within the unvisited set.
	while(unvisited_set.contains(target_node))
	{	
		if(VERBOSE)
		{
			cout << endl << "Start of iteration" << '\t' << "Current node: " << current_node << endl;
			cout << "Unvisited Set: " << endl;
			unvisited_set.print();
			cout << "Nodes Distances: " << endl;		
			print(distances);
			cout << "Node parents list: " << endl;		
			print(nodes_parents);			
		}

		//if min(distances) is infinity, then no path exists between initial and target nodes.
		if(unvisited_set.min() == INFINITY_VALUE)
		{
			simulation_result = false;
			break;
		}
		//Loop over all nodes.
		for(uint8 i=0;i<g.V();i++)
		{
			//Consider unvisited nodes that are adjacent to the current node.
			if(true == g.adjacent(current_node, i) && unvisited_set.contains(i))
			{
				//if the distance calculated through the current node is lower than the current assigned distance.
				if(distances[i] > distances[current_node] + g.get_edge_value(current_node, i))
				{
					//Update the distance and parent node.
					distances[i] = distances[current_node] + g.get_edge_value(current_node, i);
					unvisited_set.chgPrioirity(i, distances[i]);
					nodes_parents[i] = current_node;
				}
			}
		}
		//Remove the visited node from the unvisited set.
		unvisited_set.minPrioirty();
		current_node = unvisited_set.top().id;		
	}
	
	if(simulation_result == false)
	{
		if(PRINT) cout << "Simulation failed, no path exists between initial node and destination node." << endl;
	}
	else
	{
		distance_travelled = distances[target_node];
		
		for(uint32 node = target_node ;node != initial_node; )
		{
			Shortest_path_list.push_back(node);
			node = nodes_parents[node];			
		}
		reverse(Shortest_path_list.begin(), Shortest_path_list.end());
		
		if(PRINT)
		{
			cout << "Simulation succeeded!" << endl;
			cout << "Distance travelled is " << distance_travelled << endl;
			cout << "Shortest path is " << endl;
			print(Shortest_path_list);
		}
	}
	return simulation_result;
}

//Returns the distance travelled if the target node was reached.
uint32 ShortestPathAlgo::get_distance_travelled(void)
{
	return distance_travelled;
}