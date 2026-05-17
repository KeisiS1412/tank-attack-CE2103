#ifndef P2_CE2103_TANKATTACK_RANDOMMOVEMENT_H
#define P2_CE2103_TANKATTACK_RANDOMMOVEMENT_H
#include "core/graph.h"
#include "core/Pathfinding.h"


class RandomMovement
{
public:
    static Node choosePosition(Graph& graph, int row, int col);
    static Path* getMovePath(Graph& graph, int row, int col, Node dest);
};


#endif