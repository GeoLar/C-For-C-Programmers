#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "types.h"
using namespace std;

class graph
{
	private:
	vector<vector<int32> > graph_matrix;
	
	public:
	graph(uint8 size);
	void print(void);
	uint32 V(void);
	uint32 E(void);
	bool adjacent(uint32 v1, uint32 v2);
	vector<int32> neighbors(uint32 v);
	void add_edge (uint32 v1, uint32 v2);
	void delete_edge (uint32 v1, uint32 v2);
	int32 get_edge_value(uint32 v1, uint32 v2);
	void set_edge_value(uint32 v1, uint32 v2, int32 value);
	void generate(uint32 density, uint32 d1, uint32 d2);
	
};


#endif
