#ifndef DFS_H
#define DFS_H

#include "Situation.hpp"
#include "SearchNode.hpp"
#include <stack>
#include <unordered_set>
#include <memory>

std::vector<Situation> dfsSearch(const Situation& start);

#endif