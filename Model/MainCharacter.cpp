//
// Created by JOHN CHRISTIAN CASTILLO on 7/18/2021.
//

#include "MainCharacter.h"
#include "../Singletons/Timer.h"
TH::MainCharacter::MainCharacter(int lanes)
{
        /// todo: 8 divided by lanes doesnt really make sense;
        Position pos = Position(6.f / static_cast<float>(lanes) * 2, 5.5f);
        Dimensions dim = Dimensions(0.222222f, 0.444444f);
        globalBounds = std::make_shared<GlobalBounds>(pos, dim);
        movementSpeed = 5;
}
void TH::MainCharacter::setYelling(bool yell) { MainCharacter::yelling = yell; }
bool TH::MainCharacter::isScaringEnemy() const { return scareEnemy; }
void TH::MainCharacter::setScareEnemy(bool scareEnemy) { MainCharacter::scareEnemy = scareEnemy; }
float TH::MainCharacter::getScareCoolDown() const
{
        if (scareCooldown < 0) {
                return 0;
        }
        return scareCooldown;
}
void TH::MainCharacter::decrementScareCoolDown()
{
        if (scareCooldown > 0) {
                scareCooldown -= 0.1;
        }
}
void TH::MainCharacter::resetScareCoolDown() { MainCharacter::scareCooldown = 15; }
bool TH::MainCharacter::isInvincible()
{
        if (invincibleDuration <= 0) {
                invincible = false;
                invincibleDuration = 0;
        }
        return invincible;
}
void TH::MainCharacter::startInvincibility()
{
        invincible = true;
        invincibleDuration = 15.f;
}
void TH::MainCharacter::decreaseInvincibilityDuration(const float& decr)
{
        invincibleDuration -= decr;
        if (invincibleDuration < 0) {
                invincibleDuration = 0;
        }
}
const float& TH::MainCharacter::getInvincibilityDuration() const { return invincibleDuration; }
TH::EntityTypes TH::MainCharacter::getType() const { return EntityTypes::mainCharacter; }
