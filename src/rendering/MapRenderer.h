#ifndef P2_CE2103_TANKATTACK_MAPRENDERER_H
#define P2_CE2103_TANKATTACK_MAPRENDERER_H
#include "core/graph.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "ViewConfig.h"

class MapRenderer
{
private:
    ViewConfig& config;
    Graph& graph;
    sf::Texture texObstacle;
    sf::Texture texGrass;
public:
    MapRenderer(ViewConfig& config, Graph& graph);
    void renderMap(sf::RenderWindow& window);
};


#endif