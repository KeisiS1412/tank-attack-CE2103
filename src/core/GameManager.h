// ─── GameManager.h ───────────────────────────────────────────────────────────

#ifndef P2_CE2103_TANKATTACK_GAMEMANAGER_H
#define P2_CE2103_TANKATTACK_GAMEMANAGER_H

#include "Tank.h"
#include "Graph.h"
#include "powerups/PowerUpQueue.h"

// Clase central del juego. Coordina turnos, tiempo, estado de los tanques
// y el sistema de power-ups de ambos jugadores.
class GameManager {
private:
    // Arreglos de 4 punteros a tanque por jugador.
    // Jugador 1: 2 rojos y 2 azules. Jugador 2: 2 amarillos y 2 cyan.
    Tank* player1Tanks[4];
    Tank* player2Tanks[4];

    // Indica quien tiene el turno activo: 1 o 2
    int currentPlayer;

    // Tiempo maximo de la partida en segundos (300 = 5 minutos)
    float timeLimit;

    // Tiempo acumulado desde el inicio de la partida
    float elapsedTime;

    // Se activa cuando la partida termina por tiempo o eliminacion total
    bool gameOver;

    // Acumulador para generar power-ups cada 30 segundos
    float powerUpTimer;

    // Colas independientes de power-ups para cada jugador
    PowerUpQueue player1PowerUps;
    PowerUpQueue player2PowerUps;

    // Banderas que indican si hay un power-up activo en el turno actual.
    // Se activan al consumir un power-up y se resetean tras ejecutar la accion.
    bool attackPrecisionActive;  // bala sigue A*
    bool attackPowerActive;      // bala hace 100% de dano
    bool doubleTurnActive;       // el jugador actual juega dos turnos seguidos
    bool movementPrecisionActive; // aumenta probabilidad de usar algoritmo de pathfinding

    // Cuenta cuantos tanques del arreglo dado siguen con isAlive() en true
    int countAliveTanks(Tank* tanks[], int count);

    // Selecciona un tipo de power-up aleatorio y lo encola para ambos jugadores
    void generateRandomPowerUp();

public:
    // Constructor: inicializa los 8 tanques en sus posiciones de inicio
    // y resetea todos los contadores y banderas
    GameManager(Graph& graph);

    // Destructor: libera la memoria de los 8 tanques creados con new
    ~GameManager();

    // Se llama cada frame. Acumula tiempo, genera power-ups periodicamente
    // y verifica las tres condiciones de fin de partida
    void update(float deltaTime);

    // Retorna true si la partida ya termino
    bool isGameOver();

    // Retorna el jugador activo: 1 o 2
    int getCurrentPlayer();

    // Cambia el turno al otro jugador, a menos que doubleTurnActive este activo,
    // en cuyo caso solo desactiva la bandera y el turno no cambia
    void nextTurn();

    // Retorna el tiempo restante en segundos (timeLimit - elapsedTime)
    float getTimeRemaining();

    int determineWinner();

    // Accesores para obtener un tanque especifico por indice (0 a 3)
    Tank* getPlayer1Tank(int index);
    Tank* getPlayer2Tank(int index);

    // Retorna cuantos power-ups del tipo dado tiene el jugador indicado en su cola
    int getPlayerPowerUpCount(int player, PowerUpType type);

    // Saca el primer power-up de la cola del jugador activo, activa su bandera
    // correspondiente, libera la memoria y avanza el turno
    void consumePowerUp();

    // Getters de las banderas de power-up activo
    bool isAttackPrecisionActive();
    bool isAttackPowerActive();
    bool isDoubleTurnActive();
    bool isMovementPrecisionActive();

    // Desactiva todas las banderas de power-up tras ejecutar una accion
    void resetPowerUps();
};

#endif