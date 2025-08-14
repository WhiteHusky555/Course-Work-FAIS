#ifndef BFS_H
#define BFS_H

#include "Situation.hpp"
#include "SearchNode.hpp"
#include <queue>
#include <unordered_set>
#include <memory>

std::vector<Situation> bfsSearch(const Situation& start);

#endif