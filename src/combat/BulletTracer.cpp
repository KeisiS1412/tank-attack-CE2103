#include "BulletTracer.h"
#include "pathfinding/LineOfSight.h"

Path* BulletTracer::calculateTrajectory(Graph& graph, Bullet& bullet)
{
    int startRow = bullet.getStartRow();
    int startCol = bullet.getStartCol();
    int targetRow = bullet.getTargetRow();
    int targetCol = bullet.getTargetCol();

    int maxNodes = 4 * (graph.getRows() + graph.getCols());
    Path* trajectory = new Path();
    trajectory->nodes = new int[maxNodes];
    trajectory->length = 0;

    Node* cells = new Node[graph.getRows() + graph.getCols()];
    int bounces = 0;

    while (bounces <= 3)
    {
        int count = 0;
        LineOfSight::getCells(graph, startRow, startCol, targetRow, targetCol, cells, count);

        bool hitObstacle = false;

        for (int i = 0; i < count; i++)
        {
            if (graph.isObstacle(cells[i].row, cells[i].col))
            {
                if (i == 0) { hitObstacle = false; break; }

                hitObstacle = true;

                int impactRow = cells[i-1].row;
                int impactCol = cells[i-1].col;

                int dr = targetRow - impactRow;
                int dc = targetCol - impactCol;

                if (cells[i].row == cells[i-1].row) dc = -dc;
                if (cells[i].col == cells[i-1].col) dr = -dr;

                int newTargetRow = impactRow + dr;
                int newTargetCol = impactCol + dc;

                if (newTargetRow < 0) newTargetRow = 0;
                if (newTargetRow >= graph.getRows()) newTargetRow = graph.getRows() - 1;
                if (newTargetCol < 0) newTargetCol = 0;
                if (newTargetCol >= graph.getCols()) newTargetCol = graph.getCols() - 1;

                for (int j = 1; j < i; j++) {
                    trajectory->nodes[trajectory->length] = cells[j].row * graph.getCols() + cells[j].col;
                    trajectory->length++;
                }

                startRow = impactRow;
                startCol = impactCol;
                targetRow = newTargetRow;
                targetCol = newTargetCol;
                bounces++;
                break;
            }
        }

        if (!hitObstacle)
        {
            for (int i = 0; i < count; i++) {
                trajectory->nodes[trajectory->length] = cells[i].row * graph.getCols() + cells[i].col;
                trajectory->length++;
            }
            break;
        }
    }

    delete[] cells;
    return trajectory;
}