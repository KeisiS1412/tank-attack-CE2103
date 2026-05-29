#ifndef P2_CE2103_TANKATTACK_INPUTHANDLER_H
#define P2_CE2103_TANKATTACK_INPUTHANDLER_H

#include <SFML/Graphics.hpp>
#include "core/Graph.h"
#include "core/GameManager.h"
#include "core/Tank.h"
#include "core/Pathfinding.h"
#include "combat/Bullet.h"
#include "combat/BulletManager.h"

class InputHandler {
private:
    Tank* selectedTank;
    Graph& graph;

public:
    Path* currentTrace;
    Path* bulletTrace;
    Bullet* lastBullet;
    Tank* lastMovedTank;

    InputHandler(Graph& graph);
    ~InputHandler();

    void handleEvent(const sf::Event& event, GameManager& gameManager, sf::RenderWindow& window);
    Tank* getSelectedTank();
};

#endif