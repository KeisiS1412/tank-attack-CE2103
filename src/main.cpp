#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include "core/Graph.h"
#include "core/MapGenerator.h"
#include "core/GameManager.h"
#include "rendering/MapRenderer.h"
#include "rendering/TankRenderer.h"
#include "rendering/TraceRenderer.h"
#include "rendering/BulletRenderer.h"
#include "rendering/HUDRenderer.h"
#include "input/InputHandler.h"

int main() {
    srand(time(nullptr));

    Graph graph(15, 20);
    MapGenerator generator(0.2);
    generator.generate(graph);

    GameManager gameManager(graph);

    sf::RenderWindow window(sf::VideoMode({800, 650}), "Tank Attack!");
    MapRenderer mapRenderer(590, 800, graph);
    TankRenderer tankRenderer(590, 800, graph);
    TraceRenderer traceRenderer(590, 800, graph);
    BulletRenderer bulletRenderer(590, 800, graph);
    HUDRenderer hudRenderer(800, 650);
    InputHandler inputHandler(graph);

    sf::Clock clock;

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();

            inputHandler.handleEvent(*event, gameManager, window);
        }

        gameManager.update(deltaTime);

        std::string title = "Jugador " + std::to_string(gameManager.getCurrentPlayer());
        window.setTitle(title);

        window.clear(sf::Color::Black);
        mapRenderer.renderMap(window);

        if (inputHandler.currentTrace != nullptr && inputHandler.lastMovedTank != nullptr)
            traceRenderer.renderTrace(window, inputHandler.currentTrace, *inputHandler.lastMovedTank);

        if (inputHandler.bulletTrace != nullptr && inputHandler.lastBullet != nullptr)
            bulletRenderer.renderBullet(window, *inputHandler.lastBullet, inputHandler.bulletTrace);

        for (int i = 0; i < 4; i++) {
            Tank* t = gameManager.getPlayer1Tank(i);
            if (t->isAlive()) tankRenderer.renderTank(window, *t);
        }
        for (int i = 0; i < 4; i++) {
            Tank* t = gameManager.getPlayer2Tank(i);
            if (t->isAlive()) tankRenderer.renderTank(window, *t);
        }

        hudRenderer.render(window, gameManager);

        window.display();
    }

    return 0;
}