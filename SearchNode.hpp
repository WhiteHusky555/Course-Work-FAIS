#ifndef SEARCH_NODE_H
#define SEARCH_NODE_H

#include "Situation.hpp"
#include <memory>

class SearchNode {
public:
    SearchNode(const Situation& state, std::shared_ptr<SearchNode> parent = nullptr, int cost = 0, int heuristic = 0);
    
    Situation state;
    std::shared_ptr<SearchNode> parent;
    int cost;
    int heuristic;
    
    int totalCost() const;
};

#endif