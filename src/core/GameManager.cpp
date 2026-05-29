#include "GameManager.h"
#include <cstdlib>

GameManager::GameManager(Graph& graph) {
    // jugador 1: 2 rojos + 2 azules
    player1Tanks[0] = new Tank(0, 0, RED);
    player1Tanks[1] = new Tank(0, 1, RED);
    player1Tanks[2] = new Tank(1, 0, BLUE);
    player1Tanks[3] = new Tank(1, 1, BLUE);

    // jugador 2: 2 amarillos + 2 cyan
    player2Tanks[0] = new Tank(14, 19, YELLOW);
    player2Tanks[1] = new Tank(14, 18, YELLOW);
    player2Tanks[2] = new Tank(13, 19, CYAN);
    player2Tanks[3] = new Tank(13, 18, CYAN);

    currentPlayer = 1;
    timeLimit = 300.0f;
    elapsedTime = 0.0f;
    gameOver = false;
    powerUpTimer = 0.0f;
    attackPrecisionActive = false;
    attackPowerActive = false;
    doubleTurnActive = false;
    movementPrecisionActive = false;
}

GameManager::~GameManager() {
    for (int i = 0; i < 4; i++) {
        delete player1Tanks[i];
        delete player2Tanks[i];
    }
}

void GameManager::update(float deltaTime) {
    if (gameOver) return;

    elapsedTime += deltaTime;
    powerUpTimer += deltaTime;

    if (powerUpTimer >= 30.0f) {
        generateRandomPowerUp();
        powerUpTimer = 0.0f;
    }

    if (elapsedTime >= timeLimit) { gameOver = true; return; }
    if (countAliveTanks(player1Tanks, 4) == 0) { gameOver = true; return; }
    if (countAliveTanks(player2Tanks, 4) == 0) { gameOver = true; return; }
}

void GameManager::generateRandomPowerUp() {
    PowerUpType types[4] = { ATTACK_PRECISION, ATTACK_POWER, DOUBLE_TURN, MOVEMENT_PRECISION };
    PowerUpType type = types[rand() % 2];
    player1PowerUps.enqueue(type);
    player2PowerUps.enqueue(type);
}

void GameManager::consumePowerUp() {
    PowerUpQueue& queue = (currentPlayer == 1) ? player1PowerUps : player2PowerUps;
    if (queue.isEmpty()) return;

    PowerUp* p = queue.dequeue();
    if (p->type == ATTACK_PRECISION) attackPrecisionActive = true;
    if (p->type == ATTACK_POWER) attackPowerActive = true;
    if (p->type == DOUBLE_TURN) doubleTurnActive = true;
    if (p->type == MOVEMENT_PRECISION) movementPrecisionActive = true;
    delete p;
    nextTurn();
}

void GameManager::resetPowerUps() {
    attackPrecisionActive = false;
    attackPowerActive = false;
    doubleTurnActive = false;
    movementPrecisionActive = false;
}

bool GameManager::isAttackPrecisionActive() { return attackPrecisionActive; }
bool GameManager::isAttackPowerActive() { return attackPowerActive; }
bool GameManager::isDoubleTurnActive() { return doubleTurnActive; }
bool GameManager::isMovementPrecisionActive() { return movementPrecisionActive; }

int GameManager::countAliveTanks(Tank* tanks[], int count) {
    int alive = 0;
    for (int i = 0; i < count; i++)
        if (tanks[i]->isAlive()) alive++;
    return alive;
}

int GameManager::determineWinner() {
    int p1 = countAliveTanks(player1Tanks, 4);
    int p2 = countAliveTanks(player2Tanks, 4);
    if (p1 > p2) return 1;
    if (p2 > p1) return 2;
    return 0;
}

bool GameManager::isGameOver() { return gameOver; }
int GameManager::getCurrentPlayer() { return currentPlayer; }
void GameManager::nextTurn()

{
    if (doubleTurnActive)
    {
        doubleTurnActive = false;
        return;
    }
    currentPlayer = (currentPlayer == 1) ? 2 : 1;
}
float GameManager::getTimeRemaining() { return timeLimit - elapsedTime; }
Tank* GameManager::getPlayer1Tank(int index) { return player1Tanks[index]; }
Tank* GameManager::getPlayer2Tank(int index) { return player2Tanks[index]; }

int GameManager::getPlayerPowerUpCount(int player, PowerUpType type) {
    PowerUpQueue& queue = (player == 1) ? player1PowerUps : player2PowerUps;
    return queue.countByType(type);
}