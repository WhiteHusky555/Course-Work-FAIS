#include "SearchNode.hpp"

SearchNode::SearchNode(const Situation& s, std::shared_ptr<SearchNode> p, int c, int h)
    : state(s), parent(p), cost(c), heuristic(h) {}

int SearchNode::totalCost() const {
    return cost + heuristic;
}