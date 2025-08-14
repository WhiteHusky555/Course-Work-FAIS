#ifndef GRADIENT_SEARCH_H
#define GRADIENT_SEARCH_H

#include "Situation.hpp"
#include "SearchNode.hpp"
#include <queue>
#include <unordered_set>
#include <memory>

std::vector<Situation> gradientManhattanSearch(const Situation& start);
std::vector<Situation> gradientEuclidSearch(const Situation& start);

#endif