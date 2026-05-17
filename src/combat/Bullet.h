#ifndef P2_CE2103_TANKATTACK_BULLET_H
#define P2_CE2103_TANKATTACK_BULLET_H

#include "Graph.h"
#include "Tank.h"

class Bullet {
private:
    int startRow, startCol;
    int targetRow, targetCol;
    float damage;
    bool usesAStar;

public:
    Bullet(int startRow, int startCol, int targetRow, int targetCol, float damage, bool usesAStar);

    float getDamage();
    bool getUsesAStar();
    int getStartRow();
    int getStartCol();
    int getTargetRow();
    int getTargetCol();
};

#endif