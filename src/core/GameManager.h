#ifndef P2_CE2103_TANKATTACK_GAMEMANAGER_H
#define P2_CE2103_TANKATTACK_GAMEMANAGER_H

#include "Tank.h"
#include "Graph.h"
#include "powerups/PowerUpQueue.h"

class GameManager {
private:
    Tank* player1Tanks[4]; // 2 rojos y 2 azules
    Tank* player2Tanks[4]; // 2 amarillos y 2 cyan
    int currentPlayer;
    float timeLimit;
    float elapsedTime;
    bool gameOver;
    float powerUpTimer;

    PowerUpQueue player1PowerUps;
    PowerUpQueue player2PowerUps;

    bool attackPrecisionActive;
    bool attackPowerActive;
    bool doubleTurnActive;
    bool movementPrecisionActive;

    int countAliveTanks(Tank* tanks[], int count);
    int determineWinner();
    void generateRandomPowerUp();

public:
    GameManager(Graph& graph);
    ~GameManager();

    void update(float deltaTime);
    bool isGameOver();
    int getCurrentPlayer();
    void nextTurn();
    float getTimeRemaining();
    Tank* getPlayer1Tank(int index);
    Tank* getPlayer2Tank(int index);
    int getPlayer1PowerUpCount();
    int getPlayerPowerUpCount(int player, PowerUpType type);

    void consumePowerUp();
    bool isAttackPrecisionActive();
    bool isAttackPowerActive();
    bool isDoubleTurnActive();
    bool isMovementPrecisionActive();
    void resetPowerUps();
};

#endif