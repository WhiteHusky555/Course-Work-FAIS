#include "BFS.hpp"

std::vector<Situation> bfsSearch(const Situation& start) {
    std::queue<std::shared_ptr<SearchNode>> q;
    std::unordered_set<Situation, Situation::Hash> visited;
    std::vector<Situation> path;

    auto startNode = std::make_shared<SearchNode>(start);
    q.push(startNode);
    visited.insert(start);

    while (!q.empty()) {
        auto current = q.front();
        q.pop();

        if (current->state.isGoal()) { //Путь найден
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
                auto newNode = std::make_shared<SearchNode>(nextState, current, current->cost + 1);
                q.push(newNode);
            }
        }
    }

    return {};                         // Путь не найден
}