#include "GameManager.h"

GameManager::GameManager(Graph& graph) {
    // Jugador 1: dos tanques rojos
    player1Tanks[0] = new Tank(0, 0, RED);
    player1Tanks[1] = new Tank(0, 1, RED);

    // Jugador 2: dos tanques amarillos
    player2Tanks[0] = new Tank(14, 19, YELLOW);
    player2Tanks[1] = new Tank(14, 18, YELLOW);

    currentPlayer = 1;
    timeLimit = 300.0f; 
    elapsedTime = 0.0f;
    gameOver = false;
}

GameManager::~GameManager() {
    for (int i = 0; i < 2; i++) {
        delete player1Tanks[i];
        delete player2Tanks[i];
    }
}

void GameManager::update(float deltaTime) {
    if (gameOver) return;

    elapsedTime += deltaTime;

    if (elapsedTime >= timeLimit) {
        gameOver = true;
        return;
    }

    if (countAliveTanks(player1Tanks, 2) == 0) {
        gameOver = true;
        return;
    }
    if (countAliveTanks(player2Tanks, 2) == 0) {
        gameOver = true;
        return;
    }
}

int GameManager::countAliveTanks(Tank* tanks[], int count) {
    int alive = 0;
    for (int i = 0; i < count; i++) {
        if (tanks[i]->isAlive()) alive++;
    }
    return alive;
}

int GameManager::determineWinner() {
    int p1Alive = countAliveTanks(player1Tanks, 2);
    int p2Alive = countAliveTanks(player2Tanks, 2);

    if (p1Alive > p2Alive) return 1;
    if (p2Alive > p1Alive) return 2;
    return 0; 
}

bool GameManager::isGameOver() {
    return gameOver;
}

int GameManager::getCurrentPlayer() {
    return currentPlayer;
}

void GameManager::nextTurn() {
    currentPlayer = (currentPlayer == 1) ? 2 : 1;
}

float GameManager::getTimeRemaining() {
    return timeLimit - elapsedTime;
}

Tank* GameManager::getPlayer1Tank(int index) {
    return player1Tanks[index];
}

Tank* GameManager::getPlayer2Tank(int index) {
    return player2Tanks[index];
}