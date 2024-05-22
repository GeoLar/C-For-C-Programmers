#include "EdgeWeightedGraph.hpp"



EdgeWeightedGraph::EdgeWeightedGraph(int V)
	: V_{ V }, E_{ 0 }, adj_{} {
	for (int i = 0; i < V; i++) {
		adj_.push_back(std::vector<Edge> {});
	}
}

EdgeWeightedGraph::EdgeWeightedGraph(const std::string& filename) {
	std::ifstream in;
	in.open(filename);
	if (!in.is_open()) {
		std::cerr << "failed" << std::endl;
		return;
	}

	// int V;
	in >> V_;
	for (int i = 0; i < V_; i++) {
		adj_.push_back(std::vector<Edge> {});
	}

	int v{ 0 }, w{ 0 };
	double weight{ 0. };
	while (in >> v >> w >> weight) {
		Edge e{ v, w, weight };
		addEdge(e);
	}

}

void EdgeWeightedGraph::addEdge(Edge e) {
	int v = e.either();
	int w = e.other(v);
	adj_[v].push_back(e);
	adj_[w].push_back(e);
	++E_;
}

std::vector<Edge> EdgeWeightedGraph::adj(int v) const {
	return adj_[v];
}

std::vector<Edge> EdgeWeightedGraph::edges() const {
	std::vector<Edge> result{};    // including all edges
	for (int v = 0; v < V_; ++v) {
		for (Edge e : adj_[v]) {
			if (e.other(v) > v) {
				result.push_back(e);
			}
		}
	}
	return result;
}

std::string EdgeWeightedGraph::toString() const {
	std::string buffer{};
	buffer += std::to_string(V_) + " " + std::to_string(E_) + "\n";
	for (auto e : edges()) {
		buffer += e.toString();
		buffer += "\n";
	}
	return buffer;
}
// end class EdgeWeightedGraph
