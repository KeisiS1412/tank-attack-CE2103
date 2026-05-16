#include "LineOfSight.h"
#include <cmath>
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