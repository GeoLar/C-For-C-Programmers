

#include "graph.h"
#include <iostream>
#include "PriorityQueue.h"
#include <vector>
#include <algorithm>
#include "node.h"
#include "Supporting_fns.h"
#include "ShortestPathAlgo.h"

using namespace std;

void run_simulation_batch(uint32 nodes_count, uint32 gen_density)
{
	uint32 distances_sum = 0;
	uint32 successful_iter_count = 0;
	uint32 average_path_length = 0;
	
	for(uint8 i=1;i<50;i++)
	{
		ShortestPathAlgo iter(nodes_count, gen_density, 0, i);
		if(true == iter.run_simulation())
		{
			distances_sum += iter.get_distance_travelled();
			successful_iter_count += 1u;
		}
	}
	//Since distance is defined as int, and the requirement is to use a distance range 1.0 to 10.0,
	// 10 to 100 is used instead, then total distance is to be devided by 10.
	distances_sum = distances_sum/10;	
	average_path_length = distances_sum/successful_iter_count;
	
	cout << "Nodes count: " << nodes_count << " , Generation density: " << gen_density << "%" << endl;
	cout << "Total distance travelled: " << distances_sum << endl;
	cout << "Successful iterations: " << successful_iter_count << endl;
	cout << "Average path length: " << average_path_length << endl;	
}

int main()
{
	uint32 nodes_count = 50;
	uint32 gen_density = 20;
	run_simulation_batch(nodes_count, gen_density);
	gen_density = 40;
	run_simulation_batch(nodes_count, gen_density);
	gen_density = 2;
	run_simulation_batch(nodes_count, gen_density);
}