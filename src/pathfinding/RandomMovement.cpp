#include "RandomMovement.h"

#include <cstdlib>
#include <ctime>

#include "LineOfSight.h"

Node RandomMovement::choosePosition(Graph& graph, int row, int col)
{
    for (int i = 0; i < 10; i++)
    {
        int dr = (rand() % 7) - 3;
        int dc = (rand() % 7) - 3;

        int newRow = row + dr;
        int newCol = col + dc;

        if (graph.isValid(newRow, newCol) && !graph.isObstacle(newRow, newCol))
        {
            Node position;
            position.row = newRow;
            position.col = newCol;
            position.obstacle = false;
            return position;
        }
    }
    Node position;
    position.row = row;
    position.col = col;
    position.obstacle = false;
    return position;
}

Path* RandomMovement::getMovePath(Graph& graph, int row, int col, Node dest)
{
    if (!LineOfSight::hasObstacle(graph, row, col, dest.row, dest.col))
    {
        return Pathfinding::BFS(graph, row, col, dest.row, dest.col);
    }
    else
    {
        Node newStart = choosePosition(graph, row, col);
        int startRow = newStart.row;
        int startCol = newStart.col;
        return Pathfinding::BFS(graph, startRow, startCol, dest.row, dest.col);
    }
}