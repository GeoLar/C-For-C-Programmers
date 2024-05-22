/**
 * Graph.cpp
 *
 *  Created on: Dec 20, 2016
 *      Author: Michael Melachridis
 *       Email: michael.melachridis@gmail.com
 */
/*
#include "Graph.h"
#include <cassert>
#include <fstream>
#include <utility>
#include <algorithm>
#include <iterator>
#include <iomanip>
#include <iterator>
#include <iostream>
#include <string>
#include <vector>

using namespace Assignment;
typedef std::vector <int> listOfEdges;

namespace Assignment
{
	class Graph {
	public:
		Graph() :
			V(0),
			E(0),
			adjacencyList(std::vector<listOfEdges>(V)) {
		}

		Graph(int V);
		Graph(const std::string& filename);

	private:
		std::vector <listOfEdges> adjacencyList;
		int V;
		int E;
	};

	Graph::Graph(int V) :
		V(V),
		E(0),
		adjacencyList(std::vector<listOfEdges>(V)) {

		assert(V >= 0); // Number of vertices must be positive
	}

	Graph::Graph(const std::string& filename) {
		std::ifstream inFile(filename.c_str());
		std::istream_iterator<std::string> start(inFile), end;
		std::vector<std::string> uvw(start, end);

		if (!inFile.is_open()) {
			std::cout << "File: " << filename << " not found! Aborting!" << std::endl;
			exit(0);
		}

		inFile.close();

		this->V = convert<int>(uvw[0]);
		this->E = 0;
		this->adjacencyList = std::vector<listOfEdges>(V);

		for (unsigned int i = 1; i < uvw.size() - 2; i += 3) {
		int u = convert<int>(uvw[i]);
			int v = convert<int>(uvw[i + 1]);
			double w = convert<double>(uvw[i + 2]);
			this->addEdge(u, v, w);
		}
	}

	Graph::~Graph() {
		for (unsigned int i = 0; i < adjacencyList.size(); ++i) {
			listOfEdgesItr itr = adjacencyList[i].begin();

			while (itr != adjacencyList[i].end()) {
				delete* itr;
				++itr;
			}
		}
	}

	Graph* Graph::clone() const {
		Graph* g = new Graph();
		g->V = this->V;
		g->E = this->E;

		for (unsigned int i = 0; i < this->adjacencyList.size(); ++i) {
			std::copy(this->adjacencyList[i].begin(), this->adjacencyList[i].end(),
				g->adjacencyList[i].begin());
		}

		return g;
	}

	Graph::Graph(const Graph& other) {
		if (this != &other) {
			*this = other;
		}
	}

	Graph& Graph::operator=(const Graph& other) {
		if (this != &other) {
			this->V = other.V;
			this->E = other.E;

			for (unsigned int i = 0; i < other.adjacencyList.size(); ++i) {
				std::copy(other.adjacencyList[i].begin(), other.adjacencyList[i].end(), this->adjacencyList[i].begin());
			}
		}

		return *this;
	}

	bool Graph::operator==(const Graph& other) const {
		// optimization: if sizes not same, graphs not equal
		if (this->getV() != other.getV()
			|| this->getE() != other.getE()
			|| this->adjacencyList.size() != other.adjacencyList.size()) {

			return false;
		}

		for (unsigned int i = 0; i < this->adjacencyList.size(); ++i) {
			listOfEdgesConstItr thisItr = this->adjacencyList[i].begin();
			listOfEdgesConstItr otherItr = other.adjacencyList[i].begin();

			while (thisItr != adjacencyList[i].end()) {
				if ((*thisItr) != (*otherItr)) {
					return false;
				}
				++thisItr;
				++otherItr;
			}
		}

		return true;
	}

	bool Graph::operator!=(const Graph& other) const {
		return !(*this == other);
	}

	bool Graph::isAdjacent(int x, int y) const {
		assert(x > 0 || x <= V);
		assert(y > 0 || y <= V);

		listOfEdgesConstItr itr = adjacencyList[x].begin();

		while (itr != adjacencyList[x].end()) {
			if ((*itr)->getX()->getValue() == x && (*itr)->getY()->getValue() == y) {
				return true;
			}

			++itr;
		}

		return false;
	}

	const Graph::listOfEdges Graph::getNeighbors(int x) const {
		assert(x > 0 || x <= V);
		return adjacencyList[x];
	}

	bool Graph::addEdge(int x, int y, double w) {
		assert(x > 0 || x <= V);
		assert(y > 0 || y <= V);

		listOfEdgesItr itr = adjacencyList[x].begin();
		while (itr != adjacencyList[x].end()) {
			if ((*itr)->getX()->getValue() == y) {
				return false;
			}

			++itr;
		}

		E++;
		adjacencyList[x].push_back(new Edge<int>(new Node<int>(x), new Node<int>(y), w)); // weight is 0 in undirected graph

		return true;
	}

	bool Graph::removeEdge(int x, int y) {
		assert(x > 0 || x <= V);
		assert(y > 0 || y <= V);

		listOfEdgesItr itr = adjacencyList[x].begin();
		while (itr != adjacencyList[x].end()) {
			if ((*itr)->getX()->getValue() == y) {
				adjacencyList[x].remove(*itr);
				E--;
				delete* itr;
				return true;
			}

			++itr;
		}

		return false;
	}

	const Node<int>* Graph::getNodeValue(int x) const {
		assert(x > 0 || x <= V);

		listOfEdgesConstItr itr = adjacencyList[x].begin();
		while (itr != adjacencyList[x].end()) {
			if ((*itr)->getX()->getValue() == x) {
				return (*itr)->getX();
			}

			++itr;
		}

		return NULL;
	}

	void Graph::setNodeValue(int x, int a) {
		assert(x > 0 || x <= V);
		assert(a > 0 || a <= V);

		listOfEdgesConstItr itr = adjacencyList[x].begin();
		while (itr != adjacencyList[x].end()) {
			if ((*itr)->getX()->getValue() == x) {
				(*itr)->getX()->setValue(a);
			}

			++itr;
		}
	}

	const Edge<int>* Graph::getEdgeValue(int x, int y) const {
		assert(x > 0 || x <= V);
		assert(y > 0 || y <= V);

		listOfEdgesConstItr itr = adjacencyList[x].begin();
		while (itr != adjacencyList[x].end()) {
			if ((*itr)->getX()->getValue() == x && (*itr)->getY()->getValue() == y) {
				return *itr;
			}

			++itr;
		}

		return NULL;
	}

	int Graph::getDegree(int v) const {
		assert(v > 0 || v <= V);

		return adjacencyList[v].size();
	}

	std::ostream& operator<<(std::ostream& os, const Graph& graph) {
		std::stringstream ss;

		ss << "Graph (" << graph.getV() << "," << graph.getE() << ")" << std::endl;
		ss << "The Adjacency List K(" << graph.getV() << ")" << std::endl;

		for (unsigned int i = 0; i < graph.adjacencyList.size(); ++i) {
			ss << "Adjacency List[" << i << "] ";
			Graph::listOfEdgesConstItr itr = graph.adjacencyList[i].begin();

			while (itr != graph.adjacencyList[i].end()) {
				ss << std::setprecision(2);
				ss << " -> " << (*itr)->getY()->getValue() << "(" << (*itr)->getWeight() << ")";
				++itr;
			}

			ss << std::endl;
		}

		return (os << ss.str());
	}

	void Graph::generateRandomGraph(double density, double minDistance, double maxDistance) {
		const int MAX_NUM_EDGES = V * (V - 1) / 2; 			// max number of edges in complete graph = n(n-1)/2
															// see https://en.wikipedia.org/wiki/Complete_graph
		const int EDGE_LIMIT = MAX_NUM_EDGES * density + 1;

		std::cout << "MAX_NUM_EDGES: " << MAX_NUM_EDGES << std::endl;
		std::cout << "EDGE_LIMIT: " << EDGE_LIMIT << std::endl;

		srand(time(NULL));

		while (this->getE() < EDGE_LIMIT) {
			// pick two random nodes
			int x = rand() % V;// + 1;
			int y = rand() % V;// + 1;

			// check for an edge between x and y, no loops
			if (x == y || this->isAdjacent(x, y)) {
				continue; // try another edge
			}

			// create undirected edge with random distance
			double f = (double)rand() / RAND_MAX;
			double w = minDistance + f * (maxDistance - minDistance);
			this->addEdge(x, y, w);
		}
	}
}
*/