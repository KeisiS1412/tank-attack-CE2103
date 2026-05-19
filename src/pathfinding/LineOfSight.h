#ifndef P2_CE2103_TANKATTACK_LINEOFSIGHT_H
#define P2_CE2103_TANKATTACK_LINEOFSIGHT_H
#include "core/Graph.h"
#include "core/Pathfinding.h"


class LineOfSight
{
public:
    static void getCells(Graph& graph, int row1, int col1, int row2, int col2, Node* cells, int& count);
    static bool hasObstacle(Graph& graph, int row1, int col1, int row2, int col2);
    static Path* getBulletPath(Graph& graph, int startRow, int startCol, int targetRow, int targetCol, int maxBounces);
};

#endif