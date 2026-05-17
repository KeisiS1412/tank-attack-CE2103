//
// Created by HP on 17/05/2026.
//

#ifndef P2_CE2103_TANKATTACK_TRACERENDERER_H
#define P2_CE2103_TANKATTACK_TRACERENDERER_H
#include <SFML/Graphics/RenderWindow.hpp>

#include "core/Graph.h"
#include "core/Pathfinding.h"
#include "core/Tank.h"


class TraceRenderer
{
private:
    int windowH;
    int windowW;
    Graph& graph;
public:
    TraceRenderer(int windowH, int windowW, Graph& graph);
    void renderTrace(sf::RenderWindow& window, Path* path, Tank& tank);
};


#endif