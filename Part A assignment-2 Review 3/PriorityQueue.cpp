#include "PriorityQueue.h"
#include <iostream>

using namespace std;

//changes the priority (node value) of queue element.
void PriorityQueue::chgPrioirity(uint32 id, uint32 priority)
{
	priority_queue <node, vector<node>, Comparenodes > replacement_queue;
	node replacement_node;
	
	while(!distance_queue.empty())
	{
		replacement_node = distance_queue.top();
		distance_queue.pop();
		
		if(replacement_node.id == id)
		{
			replacement_node.distance = priority;
		}
		replacement_queue.push(replacement_node);
	}
	
	distance_queue.swap(replacement_queue);
}


//removes the top element of the queue.
void PriorityQueue::minPrioirty()
{
	distance_queue.pop();
}

//does the queue contain queue_element.
bool PriorityQueue::contains(uint32 id)
{
	priority_queue <node, vector<node>, Comparenodes > replacement_queue;
	node replacement_node;
	bool result = false;
	
	while(!distance_queue.empty())
	{
		replacement_node = distance_queue.top();
		distance_queue.pop();
		
		if(replacement_node.id == id)
		{
			result = true;
		}
		replacement_queue.push(replacement_node);
	}
	
	distance_queue.swap(replacement_queue);
	return result;
}

//insert queue_element into queue.	
void PriorityQueue::insert(node n)
{
	distance_queue.push(n);
}

//returns the top element of the queue.
node PriorityQueue::top()
{
	return distance_queue.top();
}

//return the number of queue_elements.
uint32 PriorityQueue::size()
{
	return distance_queue.size();
}

//Print priority queue for debugging.
void PriorityQueue::print()
{
	priority_queue <node, vector<node>, Comparenodes > replacement_queue;
	node replacement_node;
	
	cout << "Id" << '\t' << "Distance" << endl;
	while(!distance_queue.empty())
	{
		replacement_node = distance_queue.top();
		distance_queue.pop();
		
		cout << replacement_node.id << '\t' << replacement_node.distance << endl;
		
		replacement_queue.push(replacement_node);
	}
	distance_queue.swap(replacement_queue);
}


//returns the minimum value in the queue.
uint32 PriorityQueue::min()
{
	priority_queue <node, vector<node>, Comparenodes > replacement_queue;
	node replacement_node;
	uint32 minimum = INFINITY_VALUE;
	
	while(!distance_queue.empty())
	{
		replacement_node = distance_queue.top();
		distance_queue.pop();
		
		if(minimum > replacement_node.distance)
		{
			minimum = replacement_node.distance;
		}
		
		replacement_queue.push(replacement_node);
	}
	distance_queue.swap(replacement_queue);
	return minimum;
}
