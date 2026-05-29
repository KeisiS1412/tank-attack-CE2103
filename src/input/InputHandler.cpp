#include "InputHandler.h"

InputHandler::InputHandler(Graph& graph) : graph(graph) {
    selectedTank = nullptr;
    currentTrace = nullptr;
    bulletTrace = nullptr;
    lastBullet = nullptr;
    lastMovedTank = nullptr;
}

InputHandler::~InputHandler() {
    delete currentTrace;
    delete bulletTrace;
    delete lastBullet;
}

void InputHandler::handleEvent(const sf::Event& event, GameManager& gameManager, sf::RenderWindow& window) {
    if (auto* mouseClick = event.getIf<sf::Event::MouseButtonPressed>()) {
        auto winSize = window.getSize();
        float cellW = (float)winSize.x / graph.getCols();
        float cellH = (float)winSize.y / graph.getRows();
        int clickCol = mouseClick->position.x / cellW;
        int clickRow = mouseClick->position.y / cellH;

        if (mouseClick->button == sf::Mouse::Button::Left) {
            if (selectedTank != nullptr) {
                delete currentTrace;
                currentTrace = nullptr;

                Path* path = selectedTank->calculatePath(graph, clickRow, clickCol);
                if (path != nullptr) {
                    currentTrace = path;
                    int lastNode = path->nodes[path->length - 1];
                    selectedTank->moveTo(lastNode / graph.getCols(), lastNode % graph.getCols());
                }
                lastMovedTank = selectedTank;
                selectedTank = nullptr;
                gameManager.nextTurn();
            } else {
                for (int i = 0; i < 4; i++) {
                    Tank* t = (gameManager.getCurrentPlayer() == 1)
                        ? gameManager.getPlayer1Tank(i)
                        : gameManager.getPlayer2Tank(i);
                    if (t->isAlive() && t->getRow() == clickRow && t->getCol() == clickCol) {
                        selectedTank = t;
                        break;
                    }
                }
            }
        }

        if (mouseClick->button == sf::Mouse::Button::Right) {
            if (selectedTank != nullptr) {
                Tank* allTanks[8] = {
                    gameManager.getPlayer1Tank(0), gameManager.getPlayer1Tank(1),
                    gameManager.getPlayer1Tank(2), gameManager.getPlayer1Tank(3),
                    gameManager.getPlayer2Tank(0), gameManager.getPlayer2Tank(1),
                    gameManager.getPlayer2Tank(2), gameManager.getPlayer2Tank(3)
                };

                float damage = gameManager.isAttackPowerActive() ? 100.0f : selectedTank->getDamage();
                bool useAStar = gameManager.isAttackPrecisionActive();

                delete lastBullet;
                delete bulletTrace;

                lastBullet = new Bullet(
                    selectedTank->getRow(), selectedTank->getCol(),
                    clickRow, clickCol,
                    damage, useAStar
                );

                if (useAStar)
                    bulletTrace = Pathfinding::aStar(graph, selectedTank->getRow(), selectedTank->getCol(), clickRow, clickCol);
                else
                    bulletTrace = Pathfinding::dijkstra(graph, selectedTank->getRow(), selectedTank->getCol(), clickRow, clickCol);

                BulletManager::shoot(graph, *lastBullet, allTanks, 8);
                gameManager.resetPowerUps();
                lastMovedTank = selectedTank;
                selectedTank = nullptr;
                gameManager.nextTurn();
            }
        }
    }

    if (auto* keyPress = event.getIf<sf::Event::KeyPressed>()) {
        if (keyPress->code == sf::Keyboard::Key::LShift) {
            gameManager.consumePowerUp();
        }
    }
}

Tank* InputHandler::getSelectedTank() {
    return selectedTank;
}