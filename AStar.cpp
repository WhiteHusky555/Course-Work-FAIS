#include "AStar.hpp"

std::vector<Situation> aStarSearch(const Situation& start) {
    auto cmp = [](const std::shared_ptr<SearchNode>& a, const std::shared_ptr<SearchNode>& b) {
        return a->totalCost() > b->totalCost();
    };
    std::priority_queue<std::shared_ptr<SearchNode>, std::vector<std::shared_ptr<SearchNode>>, decltype(cmp)> pq(cmp);
    std::unordered_set<Situation, Situation::Hash> visited;
    std::vector<Situation> path;

    auto startNode = std::make_shared<SearchNode>(start, nullptr, 0, start.manhattanDistance());
    pq.push(startNode);
    visited.insert(start);

    while (!pq.empty()) {
        auto current = pq.top();
        pq.pop();

        if (current->state.isGoal()) {
            auto node = current;
            while (node) {
                path.push_back(node->state);
                node = node->parent;
            }
            std::reverse(path.begin(), path.end());
            return path;
        }

        auto nextStates = current->state.generateNextStates();
        for (const auto& nextState : nextStates) {
            if (visited.find(nextState) == visited.end()) {
                visited.insert(nextState);
                int heuristic = nextState.manhattanDistance();
                auto newNode = std::make_shared<SearchNode>(nextState, current, current->cost + 1, heuristic);
                pq.push(newNode);
            }
        }
    }

    return {};
}