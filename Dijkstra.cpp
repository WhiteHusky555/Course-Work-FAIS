#include "Dijkstra.hpp"
#include <limits>

struct DijkstraCompare {
    bool operator()(const std::shared_ptr<SearchNode>& a,
                   const std::shared_ptr<SearchNode>& b) {
        return a->cost > b->cost; // Минимальная стоимость сначала
    }
};

std::vector<Situation> dijkstraSearch(const Situation& start) {
    using NodePtr = std::shared_ptr<SearchNode>;
    
    std::priority_queue<NodePtr, 
                      std::vector<NodePtr>,
                      DijkstraCompare> pq;
                      
    std::unordered_map<Situation, int, Situation::Hash> cost_map;
    std::unordered_map<Situation, NodePtr, Situation::Hash> parent_map;

    // Инициализация
    auto startNode = std::make_shared<SearchNode>(start, nullptr, 0);
    pq.push(startNode);
    cost_map[start] = 0;

    while (!pq.empty()) {
        auto current = pq.top();
        pq.pop();

        // Проверка цели
        if (current->state.isGoal()) {
            std::vector<Situation> path;
            auto node = current;
            while (node) {
                path.push_back(node->state);
                node = node->parent;
            }
            std::reverse(path.begin(), path.end());
            return path;
        }

        // Пропускаем устаревшие узлы
        if (current->cost > cost_map[current->state]) continue;

        // Генерация следующих состояний
        auto nextStates = current->state.generateNextStates();
        for (const auto& nextState : nextStates) {
            // Расчет новой стоимости
            int moveCost = current->state.getMoveCost(nextState);
            int newCost = current->cost + moveCost;

            // Проверка на улучшение пути
            auto it = cost_map.find(nextState);
            if (it == cost_map.end() || newCost < it->second) {
                cost_map[nextState] = newCost;
                auto newNode = std::make_shared<SearchNode>(
                    nextState, current, newCost);
                pq.push(newNode);
                parent_map[nextState] = current;
            }
        }
    }

    return {}; // Путь не найден
}