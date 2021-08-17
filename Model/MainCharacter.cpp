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
bool TH::MainCharacter::isScaringEnemy() const { return scareEnemy; }
void TH::MainCharacter::setScareEnemy(bool _scareEnemy) { MainCharacter::scareEnemy = _scareEnemy; }
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
bool TH::MainCharacter::canSummonEnemy() const { return summonEnemy; }

bool TH::MainCharacter::isLaserActive()
{
        if (laserBeamDuration <= 0) {
                laserBeamActive = false;
                laserBeamDuration = 0;
        }
        return laserBeamActive;
}
void TH::MainCharacter::startLaserBeam()
{
        laserBeamActive = true;
        laserBeamDuration = 8.f;
}
void TH::MainCharacter::decreaseLaserBeamDuration(const float& decr)
{
        laserBeamDuration -= decr;
        if (laserBeamDuration < 0) {
                laserBeamDuration = 0;
        }
}
const float& TH::MainCharacter::getLaserBeamDuration() const { return laserBeamDuration; }

void TH::MainCharacter::setSummonEnemy(const bool& _summonEnemy) { summonEnemy = _summonEnemy; }
std::vector<std::shared_ptr<TH::GlobalBounds>> TH::MainCharacter::getLaserBeamBounds() const
{
        Position aiPos = globalBounds->position;
        Dimensions aiDim = globalBounds->dimensions;
        std::shared_ptr<GlobalBounds> frontalAura1 =
            std::make_shared<GlobalBounds>(Position(aiPos.x, aiPos.y - aiDim.height), Dimensions(aiDim));
        std::shared_ptr<GlobalBounds> frontalAura2 =
            std::make_shared<GlobalBounds>(Position(aiPos.x, aiPos.y - 2 * aiDim.height), Dimensions(aiDim));
        std::shared_ptr<GlobalBounds> frontalAura3 =
            std::make_shared<GlobalBounds>(Position(aiPos.x, aiPos.y - 3 * aiDim.height), Dimensions(aiDim));
        std::shared_ptr<GlobalBounds> frontalAura4 =
            std::make_shared<GlobalBounds>(Position(aiPos.x, aiPos.y - 4 * aiDim.height), Dimensions(aiDim));
        std::shared_ptr<GlobalBounds> frontalAura5 =
            std::make_shared<GlobalBounds>(Position(aiPos.x, aiPos.y - 5 * aiDim.height), Dimensions(aiDim));
        std::shared_ptr<GlobalBounds> frontalAura6 =
            std::make_shared<GlobalBounds>(Position(aiPos.x, aiPos.y - 6 * aiDim.height), Dimensions(aiDim));
        std::shared_ptr<GlobalBounds> frontalAura7 =
            std::make_shared<GlobalBounds>(Position(aiPos.x, aiPos.y - 7 * aiDim.height), Dimensions(aiDim));
        return {frontalAura1, frontalAura2, frontalAura3, frontalAura4, frontalAura5, frontalAura6, frontalAura7};
}