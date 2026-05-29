#include "MapRenderer.h"
#include <SFML/Graphics.hpp>

MapRenderer::MapRenderer(int windowH, int windowW, Graph& graph) : graph(graph)
{
    this-> windowH = windowH;
    this-> windowW = windowW;
    texObstacle.loadFromFile("assets/sprites/obstacle.png");
    texGrass.loadFromFile("assets/sprites/grass.png");
}

void MapRenderer::renderMap(sf::RenderWindow& window)
{
    auto size = window.getSize();
    windowW = size.x;
    windowH = size.y;

    int rows = graph.getRows();
    int cols = graph.getCols();

    float cellH = windowH / rows;
    float cellW = windowW / cols;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            sf::RectangleShape cell({cellW, cellH});
            cell.setPosition(sf::Vector2f(j * cellW, i * cellH));

            sf::Texture* tex = nullptr;
            if (graph.isObstacle(i, j)) tex = &texObstacle;
            else tex = &texGrass;

            sf::Sprite sprite(*tex);

            float scaleX = cellW / sprite.getLocalBounds().size.x;
            float scaleY = cellH / sprite.getLocalBounds().size.y;
            sprite.setScale(sf::Vector2f(scaleX, scaleY));

            sprite.setPosition(sf::Vector2f(j * cellW, i * cellH));

            window.draw(sprite);
        }
    }
}