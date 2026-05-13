#include "MapRenderer.h"
#include <SFML/Graphics.hpp>

MapRenderer::MapRenderer(int windowH, int windowW, Graph& graph) : graph(graph)
{
    this-> windowH = windowH;
    this-> windowW = windowW;
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

            if (graph.isObstacle(i, j))
                cell.setFillColor(sf::Color::Black);
            else
                cell.setFillColor(sf::Color::Green);

            window.draw(cell);
        }
    }
}