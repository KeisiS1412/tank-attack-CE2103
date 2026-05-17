#include <SFML/Graphics.hpp>
#include "core/Graph.h"
#include "core/MapGenerator.h"
#include "rendering/MapRenderer.h"
#include "core/GameManager.h"

int main() {
    Graph graph(15, 20);
    MapGenerator generator(0.2);
    generator.generate(graph);

    GameManager gameManager(graph);

    sf::RenderWindow window(sf::VideoMode({800, 600}), "Tank Attack!");
    MapRenderer renderer(600, 800, graph);

    sf::Clock clock;

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        gameManager.update(deltaTime);

        std::string title = "Tank Attack! - Jugador " +
                            std::to_string(gameManager.getCurrentPlayer()) +
                            " - Tiempo: " +
                            std::to_string((int)gameManager.getTimeRemaining()) + "s";
        window.setTitle(title);

        window.clear(sf::Color::Black);
        renderer.renderMap(window);
        window.display();
    }

    return 0;
}