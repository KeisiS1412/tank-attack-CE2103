#ifndef P2_CE2103_TANKATTACK_BULLETRENDERER_H
#define P2_CE2103_TANKATTACK_BULLETRENDERER_H
#include <SFML/Graphics/RenderWindow.hpp>

#include "combat/Bullet.h"
#include "core/Graph.h"


class BulletRenderer
{
private:
    int windowH;
    int windowW;
    Graph& graph;
public:
    BulletRenderer(int windowH, int windowW, Graph& graph);
    void renderBullet(sf::RenderWindow& window, Bullet& bullet, Path* path);
};


#endif //P2_CE2103_TANKATTACK_BULLETRENDERER_H