#ifndef P2_CE2103_TANKATTACK_TANKRENDERER_H
#define P2_CE2103_TANKATTACK_TANKRENDERER_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "ViewConfig.h"
#include "core/Tank.h"


class TankRenderer
{
private:
    ViewConfig& config;
    Graph& graph;
    sf::Texture texRed;
    sf::Texture texBlue;
    sf::Texture texYellow;
    sf::Texture texCyan;
public:
    TankRenderer(ViewConfig& config, Graph& graph);
    void renderTank(sf::RenderWindow& window, Tank& tank);
};


#endif