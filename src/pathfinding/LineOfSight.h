#ifndef P2_CE2103_TANKATTACK_LINEOFSIGHT_H
#define P2_CE2103_TANKATTACK_LINEOFSIGHT_H
#include "core/Graph.h"


class LineOfSight
{
public:
    static void getCells(Graph& graph, int row1, int col1, int row2, int col2, Node* cells, int& count);
    static bool hasObstacle(Graph& graph, int row1, int col1, int row2, int col2);
};


#endif