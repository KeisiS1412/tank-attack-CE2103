#include "BulletManager.h"

bool BulletManager::shoot(Graph& graph, Bullet& bullet, Tank* tanks[], int tankCount) {
    int startRow = bullet.getStartRow();
    int startCol = bullet.getStartCol();
    int targetRow = bullet.getTargetRow();
    int targetCol = bullet.getTargetCol();

    if (bullet.getUsesAStar()) {
        Path* path = Pathfinding::aStar(graph, startRow, startCol, targetRow, targetCol);
        if (path != nullptr) {
            for (int i = 0; i < path->length; i++) {
                int row = path->nodes[i] / graph.getCols();
                int col = path->nodes[i] % graph.getCols();
                for (int j = 0; j < tankCount; j++) {
                    if (tanks[j]->isAlive() && tanks[j]->getRow() == row && tanks[j]->getCol() == col) {
                        tanks[j]->receiveDamage(bullet.getDamage());
                        delete path;
                        return true;
                    }
                }
            }
            delete path;
        }
        return false;
    }
    bool obstacle = LineOfSight::hasObstacle(graph, startRow, startCol, targetRow, targetCol);

    if (!obstacle) {
        return checkHit(bullet, tanks, tankCount);
    }

    Node* cells = new Node[graph.getRows() + graph.getCols()];
    int count = 0;
    LineOfSight::getCells(graph, startRow, startCol, targetRow, targetCol, cells, count);

    for (int i = 0; i < count; i++) {
        if (graph.isObstacle(cells[i].row, cells[i].col)) {
            // la bala se detiene antes del obstáculo
            break;
        }
        for (int j = 0; j < tankCount; j++) {
            if (tanks[j]->isAlive() &&
                tanks[j]->getRow() == cells[i].row &&
                tanks[j]->getCol() == cells[i].col) {
                tanks[j]->receiveDamage(bullet.getDamage());
                delete[] cells;
                return true;
            }
        }
    }

    delete[] cells;
    return false;
}

bool BulletManager::checkHit(Bullet& bullet, Tank* tanks[], int tankCount) {
    for (int i = 0; i < tankCount; i++) {
        if (tanks[i]->isAlive() &&
            tanks[i]->getRow() == bullet.getTargetRow() &&
            tanks[i]->getCol() == bullet.getTargetCol()) {
            tanks[i]->receiveDamage(bullet.getDamage());
            return true;
        }
    }
    return false;
}