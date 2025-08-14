cmake_minimum_required(VERSION 3.10.0)
project(dynamic VERSION 0.1.0 LANGUAGES C CXX)

add_executable(dynamic AStar.cpp BFS.cpp BranchAndBound.cpp DFS.cpp Dijkstra.cpp GradientSearch.cpp main.cpp PriceMatch.cpp SearchNode.cpp Situation.cpp)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
