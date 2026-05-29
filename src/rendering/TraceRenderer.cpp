#include "TraceRenderer.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include "ViewConfig.h"

TraceRenderer::TraceRenderer(ViewConfig& config, Graph& graph) : graph(graph), config(config) {}
void TraceRenderer::renderTrace(sf::RenderWindow& window, Path* path, Tank& tank)
{
    if (path == nullptr || path->length < 2) return;

    int rows = graph.getRows();
    int cols = graph.getCols();

    float cellH = (float)config.mapHeight / rows;
    float cellW = (float)config.mapWidth / cols;

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
        cell.setPosition(sf::Vector2f(config.mapX + col * cellW, config.mapY + row * cellH));
        cell.setFillColor(sf::Color(color)); // semitransparente
        window.draw(cell);
    }

}