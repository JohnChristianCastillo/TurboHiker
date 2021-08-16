//
// Created by JOHN CHRISTIAN CASTILLO on 7/18/2021.
//

#include "Enemy.h"
bool TH::Enemy::isSteerRandolmy() const { return steerRandomly; }
void TH::Enemy::setSteerRandolmy(bool _steerRandomly) { Enemy::steerRandomly = _steerRandomly; }
bool TH::Enemy::exceededScareThreshold()
{
        std::shared_ptr<singleton::Random> rand = singleton::Random::getInstance();
        int randomOffset = rand->intInInterval(0, 10);
        if (randomOffset + yellPoints >= 700) {
                return true;
        }
        yellPoints += randomOffset;
        return false;
}