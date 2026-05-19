#include "LineOfSight.h"
#include <cmath>
#include <iostream>
#include "core/Graph.h"


void LineOfSight::getCells(Graph& graph, int row1, int col1, int row2, int col2, Node* cells, int& count) {
    count = 0;
    int dr = abs(row2 - row1);
    int dc = abs(col2 - col1);
    int r = row1;
    int c = col1;
    int stepR = (row2 > row1) ? 1 : -1;
    int stepC = (col2 > col1) ? 1 : -1;
    int error = dr - dc;

    while (true) {
        if (graph.isValid(r, c)) {
            cells[count].row = r;
            cells[count].col = c;
            count++;
        }
        if (r == row2 && c == col2) break;
        int err2 = 2 * error;
        if (err2 > -dc) {error -= dc; r += stepR;}
        if (err2 <  dr) {error += dr; c += stepC;}
    }
}

bool LineOfSight::hasObstacle(Graph& graph, int row1, int col1, int row2, int col2)
{
    Node* cells = new Node[graph.getRows() + graph.getCols()];
    int count;
    getCells(graph, row1, col1, row2, col2, cells, count);

    for (int i = 0; i < count; i++)
    {
        int row = cells[i].row;
        int col = cells[i].col;

        if (graph.isObstacle(row, col))
        {
            delete[] cells;
            return true;
        }

    }

    delete[] cells;
    return false;
}

static bool isBlocked(Graph& graph, int r, int c)
{
    if (!graph.isValid(r, c)) return true;
    return graph.isObstacle(r, c);
}

Path* LineOfSight::getBulletPath(Graph& graph, int startRow, int startCol,
                                 int targetRow, int targetCol, int maxBounces)
{
    int rows = graph.getRows();
    int cols = graph.getCols();

    int maxSteps = (maxBounces + 1) * (rows + cols) + 8;
    int maxNodes = maxSteps + 2;

    Path* path   = new Path();
    path->nodes  = new int[maxNodes];
    path->length = 0;

    int r = startRow;
    int c = startCol;
    path->nodes[path->length++] = r * cols + c;

    if (startRow == targetRow && startCol == targetCol)
        return path;

    int dr    = std::abs(targetRow - startRow);
    int dc    = std::abs(targetCol - startCol);
    int stepR = (targetRow > startRow) ? 1 : -1;
    int stepC = (targetCol > startCol) ? 1 : -1;
    int error = dr - dc;

    int bounces = 0;
    int steps   = 0;

    while (steps < maxSteps)
    {
        int  e2      = 2 * error;
        bool rowStep = (e2 > -dc);
        bool colStep = (e2 <  dr);

        int candR = r + (rowStep ? stepR : 0);
        int candC = c + (colStep ? stepC : 0);

        bool blocked = false;
        bool flipR   = false;
        bool flipC   = false;

        if (rowStep && colStep)
        {
            bool blkDiag = isBlocked(graph, candR, candC);
            bool blkRow  = isBlocked(graph, candR, c);
            bool blkCol  = isBlocked(graph, r, candC);

            if      (blkRow && blkCol) { blocked = true; flipR = true; flipC = true; }
            else if (blkRow)           { blocked = true; flipR = true; }
            else if (blkCol)           { blocked = true; flipC = true; }
            else if (blkDiag)          { blocked = true; flipR = true; flipC = true; }
        }
        else
        {
            if (isBlocked(graph, candR, candC))
            {
                blocked = true;
                if (rowStep) flipR = true;
                else         flipC = true;
            }
        }

        if (blocked)
        {
            if (bounces >= maxBounces) break;
            if (flipR) stepR = -stepR;
            if (flipC) stepC = -stepC;
            bounces++;
            continue;
        }

        if (rowStep) error -= dc;
        if (colStep) error += dr;
        r = candR;
        c = candC;
        path->nodes[path->length++] = r * cols + c;
        steps++;

        if (r == targetRow && c == targetCol) break;
    }

    return path;
}