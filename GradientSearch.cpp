#include "GradientSearch.hpp"

struct ManhattanCompare {
    bool operator()(const std::shared_ptr<SearchNode>& a, 
                   const std::shared_ptr<SearchNode>& b) {
        return a->state.manhattanDistance() > b->state.manhattanDistance();
    }
};

struct EuclidCompare {
    bool operator()(const std::shared_ptr<SearchNode>& a, 
                   const std::shared_ptr<SearchNode>& b) {
        return a->state.euclidDistance() > b->state.euclidDistance();
    }
};


std::vector<Situation> gradientManhattanSearch(const Situation& start) {
    std::priority_queue<std::shared_ptr<SearchNode>, 
                        std::vector<std::shared_ptr<SearchNode>>,
                        ManhattanCompare> pq;
    std::unordered_set<Situation, Situation::Hash> visited;
    std::vector<Situation> path;

    auto startNode = std::make_shared<SearchNode>(start);
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
                auto newNode = std::make_shared<SearchNode>(nextState, current);
                pq.push(newNode);
            }
        }
    }

    return {};
}

std::vector<Situation> gradientEuclidSearch(const Situation& start) {
    std::priority_queue<std::shared_ptr<SearchNode>, 
                        std::vector<std::shared_ptr<SearchNode>>,
                        EuclidCompare> pq;
    std::unordered_set<Situation, Situation::Hash> visited;
    std::vector<Situation> path;

    auto startNode = std::make_shared<SearchNode>(start);
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
                auto newNode = std::make_shared<SearchNode>(nextState, current);
                pq.push(newNode);
            }
        }
    }

    return {};
}