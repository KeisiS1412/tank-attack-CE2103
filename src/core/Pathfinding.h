#ifndef P2_CE2103_TANKATTACK_PATHFINDING_H
#define P2_CE2103_TANKATTACK_PATHFINDING_H

#include "Graph.h"

struct Path {
    int* nodes;
    int length;

    Path() : nodes(nullptr), length(0) {}
    ~Path() { delete[] nodes; }
};

class Pathfinding {
public:
    static Path* dijkstra(Graph& graph, int startRow, int startCol, int endRow, int endCol);
    static Path* aStar(Graph& graph, int startRow, int startCol, int endRow, int endCol);

private:
    static int heuristic(int row1, int col1, int row2, int col2);
};

#endif