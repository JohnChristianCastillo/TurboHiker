//
// Created by JOHN CHRISTIAN CASTILLO on 7/18/2021.
//

#include "Entity.h"
int TH::Entity::getSkin()
{
        if (skin == -1) {
                std::shared_ptr<singleton::Random> random = singleton::Random::getInstance();
                skin = random->intInInterval(1, 11);
                return skin;
        } else {
                return skin;
        }
}
float TH::Entity::getSlowingFactor() const { return slowingFactor; }
void TH::Entity::move(const float& xOffset, const float& yOffset)
{
        if (!(globalBounds->position.x + xOffset > 6 or globalBounds->position.x + xOffset < 0)) {
                globalBounds->position.x += xOffset;
                globalBounds->position.y += yOffset;
        }
}
void TH::Entity::setPosition(float x, float y)
{
        globalBounds->position.x = x;
        globalBounds->position.y = y;
}
std::shared_ptr<TH::GlobalBounds> TH::Entity::getGlobalBounds() const { return globalBounds; }
float TH::Entity::getMovementSpeed() const { return movementSpeed; }
bool TH::Entity::isSped()
{
        if (slowingFactor == 1) {
                sped = false;
        }
        return sped;
}
bool TH::Entity::isSlowed()
{
        if (slowingFactor == 1) {
                slowed = false;
        }
        return slowed;
}
void TH::Entity::slowDown()
{
        slowed = true;
        if (slowingFactor > 2) {
                slowingFactor -= 0.9;
        } else {
                slowingFactor = 0.01;
        }
}
void TH::Entity::speedUp()
{
        sped = true;
        if (slowingFactor <= 1) {
                slowingFactor += 1;
        } else {
                slowingFactor = 2;
        }
}
void TH::Entity::reduceSpeedBoostEffect(float sf)
{
        if (slowingFactor <= 1) {
                slowingFactor = 1;
        } else {
                slowingFactor = sf;
        }
}
void TH::Entity::reduceSlowingEffect(float sf)
{
        if (slowingFactor >= 1) {
                slowingFactor = 1;
        } else {
                slowingFactor = sf;
        }
}