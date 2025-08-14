#ifndef BRANCH_BOUND_H
#define BRANCH_BOUND_H

#include "Situation.hpp"
#include "SearchNode.hpp"
#include <queue>
#include <unordered_set>
#include <memory>
#include <climits>

std::vector<Situation> branchAndBoundSearch(const Situation& start);

#endif