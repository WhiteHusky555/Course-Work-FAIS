#ifndef PRICE_MATCH_H
#define PRICE_MATCH_H

#include "Situation.hpp"
#include "SearchNode.hpp"
#include <queue>
#include <unordered_set>
#include <memory>

std::vector<Situation> priceMatchSearch(const Situation& start);

#endif