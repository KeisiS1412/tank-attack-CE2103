
#ifndef P2_CE2103_TANKATTACK_MAPGENERATOR_H
#define P2_CE2103_TANKATTACK_MAPGENERATOR_H
#include "Graph.h"

class MapGenerator
{
private:
    double obstacleRatio;
    void connectNodes(Graph& graph);
    void resetMap(Graph& graph);
public:
    MapGenerator(double ratio);
    ~MapGenerator();
    void setObstacles(Graph& graph);
    void generate(Graph& graph);
};


#endif