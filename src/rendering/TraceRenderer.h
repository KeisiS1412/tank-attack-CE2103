#ifndef P2_CE2103_TANKATTACK_TRACERENDERER_H
#define P2_CE2103_TANKATTACK_TRACERENDERER_H
#include <SFML/Graphics/RenderWindow.hpp>

#include "ViewConfig.h"
#include "core/Graph.h"
#include "core/Pathfinding.h"
#include "core/Tank.h"


class TraceRenderer
{
private:
    ViewConfig& config;
    Graph& graph;
public:
    TraceRenderer(ViewConfig& config, Graph& graph);
    void renderTrace(sf::RenderWindow& window, Path* path, Tank& tank);
};


#endif