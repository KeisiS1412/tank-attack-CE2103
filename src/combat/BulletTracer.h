#ifndef P2_CE2103_TANKATTACK_BULLETTRACER_H
#define P2_CE2103_TANKATTACK_BULLETTRACER_H
#include "Bullet.h"
#include "core/Pathfinding.h"


class BulletTracer
{
public:
    static Path* calculateTrajectory(Graph& graph, Bullet& bullet);
};


#endif