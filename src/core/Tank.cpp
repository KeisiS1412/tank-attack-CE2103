#include "Tank.h"

#include "pathfinding/RandomMovement.h"

Tank::Tank(int row, int col, TankColor color) {
    this->row = row;
    this->col = col;
    this->color = color;
    this->health = 100.0f;
    this->alive = true;
}

Path* Tank::calculatePath(Graph& graph, int targetRow, int targetCol) {
    int chance = rand() % 100;

    if (color == RED || color == YELLOW) {
        if (chance < 80) {
            return Pathfinding::dijkstra(graph, row, col, targetRow, targetCol);
        }
    }
    else if (color == BLUE || color == CYAN) {
        if (chance < 50) {
            return Pathfinding::BFS(graph, row, col, targetRow, targetCol);
        }
    }

    Node dest;
    dest.row = targetRow;
    dest.col = targetCol;
    dest.obstacle = false;
    return RandomMovement::getMovePath(graph, row, col, dest);
}

void Tank::moveTo(int newRow, int newCol) {
    row = newRow;
    col = newCol;
}

float Tank::getDamage() {
    if (color == BLUE || color == CYAN)
        return 25.0f;
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