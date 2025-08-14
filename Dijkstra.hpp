#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "Situation.hpp"
#include "SearchNode.hpp"
#include <queue>
#include <unordered_map>
#include <memory>

std::vector<Situation> dijkstraSearch(const Situation& start);

#endif