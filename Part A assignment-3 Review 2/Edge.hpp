
#ifndef __EDGE_HPP__
#define __EDGE_HPP__

#include <string>
#include <exception>

/* Edge for EdgeWeightedGraph

*/
class Edge {
private:
	int v_;
	int w_;
	double weight_;

public:
	Edge() : Edge{ 0, 0, 0.0 } {}
	Edge(int v, int w, double weight)
		: v_{ v }, w_{ w }, weight_{ weight } {

	}

	inline double weight() const {
		return weight_;
	}

	inline int either() const {
		return v_;
	}

	int other(int v) const;
	std::string toString() const;
};

bool operator< (const Edge& lhs, const Edge& rhs);
bool operator> (const Edge& lhs, const Edge& rhs);

#endif // __EDGE_HPP__
