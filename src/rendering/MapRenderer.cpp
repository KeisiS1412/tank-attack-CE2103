#include "MapRenderer.h"

#include <iostream>
#include <SFML/Graphics.hpp>

#include "ViewConfig.h"

MapRenderer::MapRenderer(ViewConfig& config, Graph& graph) : graph(graph), config(config)
{
    texGrass.loadFromFile("assets/sprites/grass.png");
    texObstacle.loadFromFile("assets/sprites/obstacle.png");
}

void MapRenderer::renderMap(sf::RenderWindow& window)
{
    int rows = graph.getRows();
    int cols = graph.getCols();

    float cellH = (float)config.mapHeight / rows;
    float cellW = (float)config.mapWidth / cols;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            sf::RectangleShape cell({cellW, cellH});
            cell.setPosition(sf::Vector2f(config.mapX + j * cellW, config.mapY + i * cellH));

            sf::Texture* tex = nullptr;
            if (graph.isObstacle(i, j)) tex = &texObstacle;
            else tex = &texGrass;

            sf::Sprite sprite(*tex);

            float scaleX = cellW / sprite.getLocalBounds().size.x;
            float scaleY = cellH / sprite.getLocalBounds().size.y;
            sprite.setScale(sf::Vector2f(scaleX, scaleY));

            sprite.setPosition(sf::Vector2f(config.mapX + j * cellW, config.mapY + i * cellH));

            window.draw(sprite);
        }
    }
}