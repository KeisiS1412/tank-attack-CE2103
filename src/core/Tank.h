#ifndef P2_CE2103_TANKATTACK_TANK_H
#define P2_CE2103_TANKATTACK_TANK_H

#include "Graph.h"
#include "Pathfinding.h"
#include <cstdlib>

enum TankColor { RED, YELLOW, BLUE, CYAN };

class Tank {
private:
    int row;
    int col;
    float health;
    TankColor color;
    bool alive;

public:
    Tank(int row, int col, TankColor color);

    Path* calculatePath(Graph& graph, int targetRow, int targetCol);
    void moveTo(int newRow, int newCol);
    float getDamage();
    void receiveDamage(float amount);

    int getRow();
    int getCol();
    float getHealth();
    TankColor getColor();
    bool isAlive();
};

#endif