#include <iostream>
#include "Situation.hpp"
#include "BFS.hpp"
#include "DFS.hpp"
#include "AStar.hpp"
#include "GradientSearch.hpp"
#include "PriceMatch.hpp"
#include "BranchAndBound.hpp"
#include "Dijkstra.hpp"

void printPath(const std::vector<Situation>& path) {
    std::cout << "Path length: " << path.size() << std::endl;
    for (const auto& state : path) {
        for (const auto& row : state.getGrid()) {
            for (char c : row) std::cout << c << " ";
            std::cout << std::endl;
        }
        std::cout << "----------------" << std::endl;
    }
}

void startSearch(Situation start){
    std::cout << "BFS:" << std::endl;
    auto bfsPath = bfsSearch(start);
    printPath(bfsPath);

    std::cout << "\nDFS:" << std::endl;
    auto dfsPath = dfsSearch(start);
    printPath(dfsPath);

    std::cout << "\nGradient Manhattan Search:" << std::endl;
    auto gdPath0 = gradientManhattanSearch(start);
    printPath(gdPath0);

    std::cout << "\nGradient Euclid Search:" << std::endl;
    auto gdPath1 = gradientEuclidSearch(start);
    printPath(gdPath1);

    std::cout << "\nPrice Match Search:" << std::endl;
    auto ucPath = priceMatchSearch(start);
    printPath(ucPath);

    std::cout << "\nBranch and Bound Search:" << std::endl;
    auto bbPath = branchAndBoundSearch(start);
    printPath(bbPath);
    
    std::cout << "\nDijkstra Search:" << std::endl;
    auto DijkstraPath = dijkstraSearch(start);
    printPath(DijkstraPath);

    std::cout << "\nA* Search:" << std::endl;
    auto aStarPath = aStarSearch(start);
    printPath(aStarPath);

}

int main() {
    std::vector<std::vector<char>> grid = {
        {'0', '0', '0', 'F'},
        {'0', '1', '0', '1'},
        {'0', 'R', '1', '0'},
        {'0', '0', '0', '0'}
    };

    Situation start(grid);
    startSearch(start);
    

    return 0;
}