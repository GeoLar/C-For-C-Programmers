#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H
#include "types.h"
#include "node.h"
#include <vector>
#include <queue>
using namespace std;

class PriorityQueue
{
	private:
	priority_queue <node, vector<node>, Comparenodes > distance_queue;

	public:
	//changes the priority (node value) of queue element.
	void chgPrioirity(uint32 id, uint32 priority);
	//removes the top element of the queue.
	void minPrioirty();
	//does the queue contain queue_element.
	bool contains(uint32 id); 
	//insert queue_element into queue.	
	void insert(node n);
	//returns the top element of the queue.
	node top();
	//return the number of queue_elements.
	uint32 size();
	//Print priority queue for debugging.
	void print();
	//returns the minimum value in the queue.
	uint32 min();

};

#endif