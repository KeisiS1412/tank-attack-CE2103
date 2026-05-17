#ifndef P2_CE2103_TANKATTACK_GAMEMANAGER_H
#define P2_CE2103_TANKATTACK_GAMEMANAGER_H

#include "Tank.h"
#include "Graph.h"
#include "powerups/PowerUpQueue.h"

class GameManager {
private:
    Tank* player1Tanks[2];
    Tank* player2Tanks[2];
    int currentPlayer;
    float timeLimit;
    float elapsedTime;
    bool gameOver;
    float powerUpTimer;

    PowerUpQueue player1PowerUps;
    PowerUpQueue player2PowerUps;

    bool attackPrecisionActive;
    bool attackPowerActive;

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

    void consumePowerUp();
    bool isAttackPrecisionActive();
    bool isAttackPowerActive();
    void resetAttackPowerUps();
};

#endif