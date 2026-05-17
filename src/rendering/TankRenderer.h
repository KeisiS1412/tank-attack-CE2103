#ifndef P2_CE2103_TANKATTACK_TANKRENDERER_H
#define P2_CE2103_TANKATTACK_TANKRENDERER_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "core/Tank.h"


class TankRenderer
{
private:
    int windowH;
    int windowW;
    Graph& graph;
    sf::Texture texRed;
    sf::Texture texBlue;
    sf::Texture texYellow;
    sf::Texture texCyan;
public:
    TankRenderer(int windowH, int windowW, Graph& graph);
    void renderTank(sf::RenderWindow& window, Tank& tank);
};


#endif