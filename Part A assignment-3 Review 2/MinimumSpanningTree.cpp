#include "MinimumSpanningTree.hpp"

MinimumSpanningTree::MinimumSpanningTree(const EdgeWeightedGraph& G)
	: marked_{ std::vector<bool>(G.V(), false) }, mst_{}, pq_{}, weight_{ 0. } {

	visit_(G, 0);
	while (!pq_.empty()) {
		auto e = pq_.top();
		pq_.pop();

		int v = e.either();
		int w = e.other(v);
		if (marked_[v] && marked_[w]) {
			continue;
		}
		mst_.push(e);            // Update the MST
		weight_ += e.weight();   // Increase the weight of MST
		if (!marked_[v]) {
			visit_(G, v);
		}
		if (!marked_[w]) {
			visit_(G, w);
		}
	}
}

void MinimumSpanningTree::visit_(const EdgeWeightedGraph& G,
	int v) {
	marked_[v] = true;
	for (const Edge& e : G.adj(v)) {
		if (!marked_[e.other(v)]) {
			pq_.push(e);
		}
	}

}
