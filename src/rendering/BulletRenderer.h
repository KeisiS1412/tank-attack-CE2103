#ifndef P2_CE2103_TANKATTACK_BULLETRENDERER_H
#define P2_CE2103_TANKATTACK_BULLETRENDERER_H
#include <SFML/Graphics/RenderWindow.hpp>

#include "ViewConfig.h"
#include "combat/Bullet.h"
#include "core/Graph.h"


class BulletRenderer
{
private:
    ViewConfig& config;
    Graph& graph;
public:
    BulletRenderer(ViewConfig& config, Graph& graph);
    void renderBullet(sf::RenderWindow& window, Bullet& bullet, Path* path);
};


#endif //P2_CE2103_TANKATTACK_BULLETRENDERER_H