#ifndef P2_CE2103_TANKATTACK_HUDRENDERER_H
#define P2_CE2103_TANKATTACK_HUDRENDERER_H

#include <SFML/Graphics.hpp>
#include "core/GameManager.h"

class HUDRenderer {
private:
    sf::Font font;
    int windowW;
    int windowH;
    sf::Texture texAttackPower;
    sf::Texture texAttackPrecision;
    sf::Texture texDoubleTurn;
    sf::Texture texMovement;

public:
    HUDRenderer(int windowW, int windowH);
    void render(sf::RenderWindow& window, GameManager& gameManager);
};

#endif