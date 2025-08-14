#include "Situation.hpp"
#include <functional>
#include "cmath"

Situation::Situation(const std::vector<std::vector<char>>& g) : grid(g) {
    locateRobot();
    locateFinish();
}



Situation::Situation(const Situation& other) 
    : grid(other.grid), robotX(other.robotX), robotY(other.robotY),
      finishX(other.finishX), finishY(other.finishY) {}

void Situation::locateRobot() {
    for (int i = 0; i < grid.size(); ++i)
        for (int j = 0; j < grid[i].size(); ++j)
            if (grid[i][j] == 'R') {
                robotX = i;
                robotY = j;
                return;
            }
}

void Situation::locateFinish() {
    for (int i = 0; i < grid.size(); ++i)
        for (int j = 0; j < grid[i].size(); ++j)
            if (grid[i][j] == 'F') {
                finishX = i;
                finishY = j;
                return;
            }
}

bool Situation::isGoal() const {
    return robotX == finishX && robotY == finishY;
}

bool Situation::isFatal() const {
    if (isGoal()) return false;
    return generateNextStates().empty();
}

int Situation::manhattanDistance() const {
    return abs(robotX - finishX) + abs(robotY - finishY);
}

int Situation::euclidDistance() const{
    return sqrt(pow(robotX - finishX, 2) + pow(robotY - finishY, 2));
}

std::vector<Situation> Situation::generateNextStates() const {
    std::vector<Situation> nextStates;
    const std::vector<std::pair<int, int>> directions = {{-1,0}, {1,0}, {0,-1}, {0,1}};

    for (const auto& dir : directions) {
        int newX = robotX + dir.first;
        int newY = robotY + dir.second;

        if (newX < 0 || newX >= grid.size() || newY < 0 || newY >= grid[0].size())
            continue;

        char target = grid[newX][newY];

        if (target == '0' || target == 'F') {
            Situation newState(*this);
            newState.grid[robotX][robotY] = '0';
            newState.grid[newX][newY] = 'R';
            newState.robotX = newX;
            newState.robotY = newY;
            nextStates.push_back(newState);
        } else if (target == '1') {
            int behindX = newX + dir.first;
            int behindY = newY + dir.second;

            if (behindX >= 0 && behindX < grid.size() && behindY >= 0 && behindY < grid[0].size() && grid[behindX][behindY] == '0') {
                Situation newState(*this);
                newState.grid[robotX][robotY] = '0';
                newState.grid[newX][newY] = 'R';
                newState.grid[behindX][behindY] = '1';
                newState.robotX = newX;
                newState.robotY = newY;
                nextStates.push_back(newState);
            }
        }
    }

    return nextStates;
}

int Situation::getMoveCost(const Situation& nextState) const {
        // Проверяем, было ли толкание препятствия
        if (std::abs(robotX - nextState.robotX) + 
            std::abs(robotY - nextState.robotY) > 1) {
            return 2; // Стоимость толкания
        }
        return 1; // Обычное перемещение
    }

bool Situation::operator==(const Situation& other) const {
    return grid == other.grid;
}

size_t Situation::Hash::operator()(const Situation& s) const {
    std::string repr;
    for (const auto& row : s.grid)
        for (char c : row) repr += c;
    return std::hash<std::string>()(repr);
}