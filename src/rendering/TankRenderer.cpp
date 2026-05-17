#include "TankRenderer.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>

TankRenderer::TankRenderer(int windowH, int windowW, Graph& graph) : graph(graph)
{
    this-> windowH = windowH;
    this-> windowW = windowW;
    texRed.loadFromFile("assets/sprites/tank-red.png");
    texBlue.loadFromFile("assets/sprites/tank-blue.png");
    texYellow.loadFromFile("assets/sprites/tank-yellow.png");
    texCyan.loadFromFile("assets/sprites/tank-cyan.png");
}

void TankRenderer::renderTank(sf::RenderWindow& window, Tank& tank)
{
    auto size = window.getSize();
    windowW = size.x;
    windowH = size.y;

    int rows = graph.getRows();
    int cols = graph.getCols();

    float cellH = windowH / rows;
    float cellW = windowW / cols;

    int row = tank.getRow();
    int col = tank.getCol();

    sf::Texture* tex = nullptr;
    if (tank.getColor() == RED) tex = &texRed;
    else if (tank.getColor() == BLUE) tex = &texBlue;
    else if (tank.getColor() == YELLOW) tex = &texYellow;
    else if (tank.getColor() == CYAN) tex = &texCyan;

    sf::Sprite sprite(*tex);

    float scaleX = cellW / sprite.getLocalBounds().size.x;
    float scaleY = cellH / sprite.getLocalBounds().size.y;
    sprite.setScale(sf::Vector2f(scaleX, scaleY));

    sprite.setPosition(sf::Vector2f(col * cellW, row * cellH));

    window.draw(sprite);
}