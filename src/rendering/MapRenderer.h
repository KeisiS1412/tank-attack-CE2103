#ifndef P2_CE2103_TANKATTACK_MAPRENDERER_H
#define P2_CE2103_TANKATTACK_MAPRENDERER_H
#include "core/graph.h"
#include <SFML/Graphics/RenderWindow.hpp>

class MapRenderer
{
private:
    int windowH;
    int windowW;
    Graph& graph;
public:
    MapRenderer(int windowH, int windowW, Graph& graph);
    void renderMap(sf::RenderWindow& window);
};


#endif