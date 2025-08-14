#ifndef ASTAR_H
#define ASTAR_H

#include "Situation.hpp"
#include "SearchNode.hpp"
#include <queue>
#include <unordered_set>
#include <memory>

std::vector<Situation> aStarSearch(const Situation& start);

#endif