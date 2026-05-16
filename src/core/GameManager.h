#ifndef P2_CE2103_TANKATTACK_GAMEMANAGER_H
#define P2_CE2103_TANKATTACK_GAMEMANAGER_H

#include "Tank.h"
#include "Graph.h"

class GameManager {
private:
    Tank* player1Tanks[2]; // rojo y amarillo
    Tank* player2Tanks[2]; // rojo y amarillo 
    int currentPlayer;
    float timeLimit;
    float elapsedTime;
    bool gameOver;

    int countAliveTanks(Tank* tanks[], int count);
    int determineWinner();

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
};

#endif