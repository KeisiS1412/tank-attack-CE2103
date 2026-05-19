#include "BulletTracer.h"
#include "pathfinding/LineOfSight.h"

Path* BulletTracer::calculateTrajectory(Graph& graph, Bullet& bullet)
{
    return LineOfSight::getBulletPath(
        graph,
        bullet.getStartRow(),
        bullet.getStartCol(),
        bullet.getTargetRow(),
        bullet.getTargetCol(),
        3
    );
}