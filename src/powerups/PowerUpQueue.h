#ifndef P2_CE2103_TANKATTACK_POWERUPQUEUE_H
#define P2_CE2103_TANKATTACK_POWERUPQUEUE_H

#include "PowerUp.h"

class PowerUpQueue {
private:
    struct Node {
        PowerUp* data;
        Node* next;
    };
    Node* front;
    Node* back;

public:
    PowerUpQueue();
    ~PowerUpQueue();

    void enqueue(PowerUpType type);
    PowerUp* dequeue();
    PowerUp* peek();
    bool isEmpty();
};

#endif