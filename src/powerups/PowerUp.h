#ifndef P2_CE2103_TANKATTACK_POWERUP_H
#define P2_CE2103_TANKATTACK_POWERUP_H

enum PowerUpType {
    DOUBLE_TURN,
    MOVEMENT_PRECISION,
    ATTACK_PRECISION,
    ATTACK_POWER
};

struct PowerUp {
    PowerUpType type;
    bool applied;

    PowerUp(PowerUpType type) {
        this->type = type;
        this->applied = false;
    }
};

#endif