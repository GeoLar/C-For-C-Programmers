#ifndef NODE_H
#define NODE_H


struct node
{
	uint32 id;
	int32 distance;
	node(uint32 id, int32 distance) : id(id), distance(distance) {}
	node() : id(0), distance(0) {}	
};

struct Comparenodes 
{ 
	bool operator()(node const& n1, node const& n2) 
	{ 
		// return "true" if "n1" is ordered  
		// before "n2", for example: 
		return n1.distance > n2.distance; 
	} 
}; 

#endif