// Program to find Dijkstra's shortest path using 
// priority_queue in STL 
//#include<bits/stdc++.h> 
#include<iostream>
#include<vector>
#include<queue>
#include<random>
using namespace std;
static const float INF = FLT_MAX;
static const int MAX_VERTEX_NUMBER = 100; // Maximum Number of vertices in a generated graph
// Node ==> Integer Pair 
typedef pair<int, int> Node;
class UGraph
{
	int graphSize;
	vector< pair<int, int> >* adj;
public:
	UGraph(int graphSize)
	{
		this->graphSize = graphSize;
		adj = new vector<Node>[graphSize];
	}
	// To add an edge 
	void addEdge(int u, int  v, int wt)
	{
		adj[u].push_back(make_pair(v, wt));
		adj[v].push_back(make_pair(u, wt));
	}


	// Prints shortest paths from src to all other vertices 
	float shortestPath(int src)
	{
		// Create a priority queue to store vertices that 
		// are being preprocessed. 	 
		priority_queue< Node, vector <Node>, greater<Node> > pq;

		// Create a vector for distances and initialize all 
		// distances as infinite (INF) 
		vector<float> dist(graphSize, INF);

		// Insert source itself in priority queue and initialize 
		// its distance as 0. 
		pq.push(make_pair(0, src));
		dist[src] = 0;

		/* Looping till priority queue becomes empty (or all
		distances are not finalized) */
		while (!pq.empty())
		{
			// The first vertex in pair is the minimum distance 
			// vertex, extract it from priority queue. 
			// vertex label is stored in second of pair (it 
			// has to be done this way to keep the vertices 
			// sorted distance (distance must be first item 
			// in pair) 
			int u = pq.top().second;
			pq.pop();

			// Get all adjacent of u. 
			for (int i = 0; i < adj[u].size(); i++)//auto x : adj[u]) 
			{
				// Get vertex label and weight of current adjacent 
				// of u. 
				int v = adj[u][i].first;
				int weight = adj[u][i].second;

				// If there is shorted path to v through u. 
				if (dist[v] > dist[u] + weight)
				{
					// Updating distance of v 
					dist[v] = dist[u] + weight;
					pq.push(make_pair(dist[v], v));
				}
			}
		}

		// Print shortest distances stored in dist[] 
		//cout<<"Vertex Distance from Source"<<endl;
		float distances = 0;
		for (int i = 0; i < graphSize; ++i)
		{
			distances += dist[i];
		}

		return (distances / static_cast<float>(graphSize));
	}
};
class GraphSimulation
{
	float density;
	float distRange;
	int graphSize;
	int numberTrials;
public:
	GraphSimulation(float density, float range, int graphSize, int numberTrials) :density(density), distRange(range), graphSize(graphSize), numberTrials(numberTrials) {}
	float averageShortestPath()
	{
		float length = 0.0; // lenght of the shortest path
		for (int i = 0; i < numberTrials; i++)
		{
			float number = static_cast<float>(rand()) / RAND_MAX;
			UGraph myGraph(graphSize);
			// Random numbers generator following this https://channel9.msdn.com/Events/GoingNative/2013/rand-Considered-Harmful
			std::random_device rd;
			std::mt19937 mt(rd());
			std::uniform_real_distribution<double> den(0.0, 1.0);
			std::uniform_real_distribution<double> dis(0.0, distRange);

			int n = 0;
			for (int u = 0; u < graphSize; u++)
			{
				for (int v = 0; v < graphSize; v++)
				{

					float prob = den(mt);
//					cout << "probability: " << prob << endl;
					if ((den(mt)) < density && (u != v))
					{
						myGraph.addEdge(u, v, dis(mt));
						n += 1;
					}
				}
			}

			// Calculate shortest path for every node in the graph

			length = myGraph.shortestPath(0);


		}
		return length / numberTrials;
	}
};
// Driver program to test methods of graph class 
int main()
{
	cout << "What I 've learned is that OO programming is a very different approach to problems" << endl;
	cout << "I am still not very sure on my abilities to write a set of classes that cannot solve a problem" << endl;
	cout << "using this approach, I had to make o a lot of research, read a lot of web sites articles about" << endl;
	cout << "min heaps, graph theory, graphs in CS, random numbers generators, I decided to use STL to implement undirected graph, min priority heap" << endl;
	cout << "and the random number generator caused me some pain since ot seems to be broken sometimes, " << endl;
	cout << "My conclusion after the montecarlo simulation is that for more density the mean path is shorter," << endl;
	cout << "this is expected sinde we have a graph with 0 density this means we have not connected edges, and the shortest path is infinity," << endl;
	cout << "so if we have a 100% connected graph, is very probable we can find a vary short path. " << endl;
	float densities[2] = { 0.1,0.4 };
	float distances[10] = { 1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0 };
	float meanLenDensity = 0;
	float meanLenDistance = 0;
	int nodesNumber = 50; // just a fixed number
	int numberOfTrials = 10; // number of simulations
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			GraphSimulation simulation(densities[j], distances[i], nodesNumber, numberOfTrials);

			cout << "density:" << densities[j] << " range: " << distances[i] << " mean shortest: " << simulation.averageShortestPath() << endl;

		}

	}

	return 0;
}

