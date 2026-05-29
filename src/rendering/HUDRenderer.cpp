#include "HUDRenderer.h"

HUDRenderer::HUDRenderer(int windowW, int windowH) {
    this->windowW = windowW;
    this->windowH = windowH;
    font.openFromFile("assets/fonts/poppins.light.ttf");
}

void HUDRenderer::render(sf::RenderWindow& window, GameManager& gameManager) {
    auto size = window.getSize();
    windowW = size.x;
    windowH = size.y;

    float hudWidth = 600.0f;
    float hudX = (windowW - hudWidth) / 2;

    sf::RectangleShape hudBar({hudWidth, 60.0f});
    hudBar.setPosition(sf::Vector2f(hudX, windowH - 60));
    hudBar.setFillColor(sf::Color(0, 0, 0, 180));
    window.draw(hudBar);

    int totalSeconds = (int)gameManager.getTimeRemaining();
    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;
    std::string timeStr = "Tiempo: " + std::to_string(minutes) + ":" +
                          (seconds < 10 ? "0" : "") + std::to_string(seconds);

    sf::Text timeText(font, timeStr, 14);
    timeText.setFillColor(sf::Color::White);
    timeText.setPosition(sf::Vector2f(windowW / 2 - 40, windowH - 50));
    window.draw(timeText);

    std::string turnStr = "Turno: Jugador " + std::to_string(gameManager.getCurrentPlayer());
    sf::Text turnText(font, turnStr, 14);
    turnText.setFillColor(gameManager.getCurrentPlayer() == 1 ? sf::Color::Red : sf::Color::Yellow);
    turnText.setPosition(sf::Vector2f(windowW / 2 - 52, windowH - 30));
    window.draw(turnText);

    std::string p1Str = "J1: ";
    for (int i = 0; i < 4; i++) {
        Tank* t = gameManager.getPlayer1Tank(i);
        if (t->isAlive()) p1Str += std::to_string((int)t->getHealth()) + "% ";
        else p1Str += "X ";
    }
    sf::Text p1Text(font, p1Str, 14);
    p1Text.setFillColor(sf::Color::Red);
    p1Text.setPosition(sf::Vector2f(hudX + 10, windowH - 50));
    window.draw(p1Text);

    std::string p2Str = "J2: ";
    for (int i = 0; i < 4; i++) {
        Tank* t = gameManager.getPlayer2Tank(i);
        if (t->isAlive()) p2Str += std::to_string((int)t->getHealth()) + "% ";
        else p2Str += "X ";
    }
    sf::Text p2Text(font, p2Str, 14);
    p2Text.setFillColor(sf::Color::Yellow);
    p2Text.setPosition(sf::Vector2f(hudX + hudWidth - 180, windowH - 50));
    window.draw(p2Text);

    if (gameManager.isGameOver()) {
        sf::RectangleShape overlay({(float)windowW, (float)windowH});
        overlay.setFillColor(sf::Color(0, 0, 0, 150));
        window.draw(overlay);

        sf::Text gameOverText(font, "GAME OVER", 50);
        gameOverText.setFillColor(sf::Color::White);
        gameOverText.setPosition(sf::Vector2f(windowW / 2 - 120, windowH / 2 - 30));
        window.draw(gameOverText);
    }
}