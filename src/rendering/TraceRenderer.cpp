#include "TraceRenderer.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
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

    int opacity = 150;

    sf::Color color;
    if (tank.getColor() == RED) color = sf::Color(255, 0, 0, opacity);
    else if (tank.getColor() == BLUE) color = sf::Color(0, 0, 255, opacity);
    else if (tank.getColor() == YELLOW) color = sf::Color(255, 255, 0, opacity);
    else color = sf::Color(0, 255, 255, opacity);

    for (int i = 0; i < path->length; i++) {
        int row = path->nodes[i] / cols;
        int col = path->nodes[i] % cols;

        sf::RectangleShape cell({cellW, cellH});
        cell.setPosition(sf::Vector2f(col * cellW, row * cellH));
        cell.setFillColor(sf::Color(color)); // semitransparente
        window.draw(cell);
    }

}