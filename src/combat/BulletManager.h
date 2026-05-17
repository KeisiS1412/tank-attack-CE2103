#ifndef P2_CE2103_TANKATTACK_BULLETMANAGER_H
#define P2_CE2103_TANKATTACK_BULLETMANAGER_H

#include "Bullet.h"
#include "../core/Graph.h"
#include "../core/Tank.h"
#include "../core/Pathfinding.h"
#include "../pathfinding/LineOfSight.h"

class BulletManager {
public:
    // dispara una bala y aplica daño si golpea algo
    // retorna true si golpeó un tanque
    static bool shoot(Graph& graph, Bullet& bullet, Tank* tanks[], int tankCount);

private:
    static bool checkHit(Bullet& bullet, Tank* tanks[], int tankCount);
};

#endif