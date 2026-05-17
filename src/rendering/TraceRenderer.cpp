#include "TraceRenderer.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/VertexArray.hpp>

TraceRenderer::TraceRenderer(int windowH, int windowW, Graph& graph) : graph(graph)
{
    this-> windowH = windowH;
    this-> windowW = windowW;
}

void TraceRenderer::renderTrace(sf::RenderWindow& window, Path* path, Tank& tank)
{
    if (path == nullptr || path->length < 2) return;
    
    auto size = window.getSize();
    windowW = size.x;
    windowH = size.y;

    int rows = graph.getRows();
    int cols = graph.getCols();

    float cellH = windowH / rows;
    float cellW = windowW / cols;

    sf::VertexArray lines(sf::PrimitiveType::Lines, (path->length - 1) * 2);

    float radius = cellW / 10;
    sf::CircleShape dot(radius);

    for (int i = 0; i < path->length - 1; i++) {
        int row1 = path->nodes[i] / cols;
        int col1 = path->nodes[i] % cols;
        int row2 = path->nodes[i+1] / cols;
        int col2 = path->nodes[i+1] % cols;

        float x1 = col1 * cellW + cellW / 2;
        float y1 = row1 * cellH + cellH / 2;
        float x2 = col2 * cellW + cellW / 2;
        float y2 = row2 * cellH + cellH / 2;

        lines[i * 2].position = sf::Vector2f(x1, y1);
        lines[i * 2 + 1].position = sf::Vector2f(x2, y2);

        sf::Color color;
        if (tank.getColor() == RED) color = sf::Color::Red;
        else if (tank.getColor() == BLUE) color = sf::Color::Blue;
        else if (tank.getColor() == YELLOW) color = sf::Color::Yellow;
        else color = sf::Color::Cyan;

        lines[i * 2].color = color;
        lines[i * 2 + 1].color = color;

        int lastNode = path->nodes[path->length - 1];
        int destRow = lastNode / cols;
        int destCol = lastNode % cols;
        dot.setPosition(sf::Vector2f(destCol * cellW + cellW / 2 - radius, destRow * cellH + cellH / 2 - radius));
        dot.setFillColor(color);
    }

    window.draw(lines);
    window.draw(dot);
}