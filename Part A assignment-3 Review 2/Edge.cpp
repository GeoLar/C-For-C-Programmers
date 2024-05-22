#include <exception>
#include <iostream>

#include "Edge.hpp"


int Edge::other(int v) const {
    if (v == v_) {
        return w_;
    } else if (v == w_) {
        return v_;
    } else {
        std::cerr << "invalid implementation: other vertice is not available." \
            << std::endl;
        return -1;
    }
}
std::string Edge::toString() const {
    std::string buffer;
    return buffer + std::to_string(v_) + "-" + std::to_string(w_) + " " + std::to_string(weight_);
    //return buffer;
}

bool operator< (const Edge& lhs, const Edge& rhs) {
    if (lhs.weight() < rhs.weight()) {
        return true;
    } else {
        return false;
    }
}

bool operator> (const Edge& lhs, const Edge& rhs) {
    if (lhs.weight() > rhs.weight()) {
        return true;
    } else {
        return false;
    }
}
