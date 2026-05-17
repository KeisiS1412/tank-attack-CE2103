#include "Bullet.h"

Bullet::Bullet(int startRow, int startCol, int targetRow, int targetCol, float damage, bool usesAStar) {
    this->startRow = startRow;
    this->startCol = startCol;
    this->targetRow = targetRow;
    this->targetCol = targetCol;
    this->damage = damage;
    this->usesAStar = usesAStar;
}

float Bullet::getDamage() { return damage; }
bool Bullet::getUsesAStar() { return usesAStar; }
int Bullet::getStartRow() { return startRow; }
int Bullet::getStartCol() { return startCol; }
int Bullet::getTargetRow() { return targetRow; }
int Bullet::getTargetCol() { return targetCol; }