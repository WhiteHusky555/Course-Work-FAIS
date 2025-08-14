#include "BranchAndBound.hpp"
#include <unordered_map>

struct BBCompare {
    bool operator()(const std::shared_ptr<SearchNode>& a,
                   const std::shared_ptr<SearchNode>& b) {
        return a->cost > b->cost; // Минимальная стоимость сначала
    }
};

std::vector<Situation> branchAndBoundSearch(const Situation& start) {
    std::priority_queue<std::shared_ptr<SearchNode>,
                      std::vector<std::shared_ptr<SearchNode>>,
                      BBCompare> pq;
    std::unordered_map<Situation, int, Situation::Hash> best_costs;
    std::vector<Situation> path;
    static int global_best = INT_MAX;

    auto startNode = std::make_shared<SearchNode>(start, nullptr, 0);
    pq.push(startNode);
    best_costs[start] = 0;

    while (!pq.empty()) {
        auto current = pq.top();
        pq.pop();

        // Отсечение ветвей, если текущий путь хуже известного
        if (current->cost > global_best) continue;

        if (current->state.isGoal()) {
            if (current->cost < global_best) {
                global_best = current->cost;
                // Сохраняем новый лучший путь
                path.clear();
                auto node = current;
                while (node) {
                    path.push_back(node->state);
                    node = node->parent;
                }
                std::reverse(path.begin(), path.end());
            }
            continue;
        }

        auto nextStates = current->state.generateNextStates();
        for (const auto& nextState : nextStates) {
            // Расчет новой стоимости
            int moveCost = current->state.getMoveCost(nextState);
            int newCost = current->cost + moveCost;
            
            // Проверяем есть ли уже лучшее решение для этого состояния
            auto it = best_costs.find(nextState);
            if (it == best_costs.end() || newCost < it->second) {
                best_costs[nextState] = newCost;
                auto newNode = std::make_shared<SearchNode>(
                    nextState, current, newCost);
                pq.push(newNode);
            }
        }
    }

    return path;
}