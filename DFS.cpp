#include "DFS.hpp"

std::vector<Situation> dfsSearch(const Situation& start) {
    std::stack<std::shared_ptr<SearchNode>> stack;
    std::unordered_set<Situation, Situation::Hash> visited;
    std::vector<Situation> path;

    auto startNode = std::make_shared<SearchNode>(start);
    stack.push(startNode);
    visited.insert(start);

    while (!stack.empty()) {
        auto current = stack.top();
        stack.pop();

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
                auto newNode = std::make_shared<SearchNode>(nextState, current);
                stack.push(newNode);
            }
        }
    }

    return {};                         //Путь не найден
}