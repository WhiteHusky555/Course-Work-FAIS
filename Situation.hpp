#ifndef SITUATION_H
#define SITUATION_H

#include <vector>
#include <string>
#include <algorithm>

class Situation {
public:
    Situation(const std::vector<std::vector<char>>& grid);
    Situation(const Situation& other);
    static int distancetype;
    bool isGoal() const;
    bool isFatal() const;
    int manhattanDistance() const;
    int euclidDistance() const;
    std::vector<Situation> generateNextStates() const;
    
    bool operator==(const Situation& other) const;
    struct Hash;
    
    const std::vector<std::vector<char>>& getGrid() const { return grid; }

    int getMoveCost(const Situation& nextState) const; 

private:
    std::vector<std::vector<char>> grid;
    int robotX, robotY;
    int finishX, finishY;
    
    void locateRobot();
    void locateFinish();
};

struct Situation::Hash {
    size_t operator()(const Situation& s) const;
};

#endif