//
// Created by JOHN CHRISTIAN CASTILLO on 7/18/2021.
//

#include "Enemy.h"
bool Enemy::isCollided() const {
    return collided;
}
void Enemy::setCollided(bool collided) {
    Enemy::collided = collided;
}
