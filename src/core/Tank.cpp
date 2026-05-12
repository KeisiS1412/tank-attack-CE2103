#include "Tank.h"

Tank::Tank(int row, int col, TankColor color) {
    this->row = row;
    this->col = col;
    this->color = color;
    this->health = 100.0f;
    this->alive = true;
}

Path* Tank::calculatePath(Graph& graph, int targetRow, int targetCol) {
    int chance = rand() % 100;

    if (chance < 80) {
        return Pathfinding::dijkstra(graph, row, col, targetRow, targetCol);
    }

    Node neighbors[4];
    int count = 0;
    graph.getNeighbors(row, col, neighbors, count);

    if (count == 0) return nullptr;

    int randomIdx = rand() % count;
    int randomRow = neighbors[randomIdx].row;
    int randomCol = neighbors[randomIdx].col;

    return Pathfinding::dijkstra(graph, row, col, randomRow, randomCol);
}

void Tank::moveTo(int newRow, int newCol) {
    row = newRow;
    col = newCol;
}

float Tank::getDamage() {
    return 50.0f;
}

void Tank::receiveDamage(float amount) {
    health -= amount;
    if (health <= 0) {
        health = 0;
        alive = false;
    }
}

int Tank::getRow() { return row; }
int Tank::getCol() { return col; }
float Tank::getHealth() { return health; }
TankColor Tank::getColor() { return color; }
bool Tank::isAlive() { return alive; }