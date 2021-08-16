//
// Created by JOHN CHRISTIAN CASTILLO on 7/18/2021.
//

#ifndef TURBOHIKER_MAINCHARACTER_H
#define TURBOHIKER_MAINCHARACTER_H

#include "Entity.h"
#include <vector>

namespace TH {
class MainCharacter : public Entity
{
        bool yelling{false};
        bool scareEnemy{false};

public:
        void resetScareCooldown();
        void decrementScareCooldown()
        {
                if (scareCooldown > 0) {
                        // std::cout << "decremented to:" << scareCooldown;
                        scareCooldown -= 0.1;
                }
        }

private:
        float scareCooldown{0};
        bool invincible{false};

public:
        void setInvincible(bool invincible);

private:
        float invincibleDuration{0};

public:
        float getScareCooldown() const;

        bool isInvincible()
        {
                if (invincibleDuration <= 0) {
                        invincible = false;
                        invincibleDuration = 0;
                }
                return invincible;
        }
        void startInvincibility()
        {
                invincible = true;
                invincibleDuration = 15.f;
        }
        void decreaseInvincibilityDuration(const float& decr)
        {
                invincibleDuration -= decr;
                if (invincibleDuration < 0) {
                        invincibleDuration = 0;
                }
        }

        const float& getInvincibilityDuration() const { return invincibleDuration; }
        bool isScaringEnemy();
        void setScareEnemy(bool scareEnemy);

public:
        bool isYelling() const;
        void setYelling(bool yelling);

        /**
         * in a (-4,4) (-3,3) coordinate system. Our character needs to be placed at the lowest-middle
         * part of the screen
         * screen:
         *              6
         *       _______________
         *      |              |
         *      |              |
         *      |              |
         *    8 |              |
         *      |              |
         *      |              |
         *      |_____char_____|
         */

public:
        MainCharacter(int lanes);
        EntityTypes getType() const override { return EntityTypes::mainCharacter; }

        /**
         *
         * @return the area around the main character affected by it's yell/honk
         */
        std::vector<std::shared_ptr<GlobalBounds>> getAura()
        {
                Position mcPos = globalBounds->position;
                Dimentions mcDim = globalBounds->dimentions;
                std::shared_ptr<GlobalBounds> frontalAura1 =
                    std::make_shared<GlobalBounds>(Position(mcPos.x, mcPos.y - mcDim.height), Dimentions(mcDim));
                std::shared_ptr<GlobalBounds> frontalAura2 =
                    std::make_shared<GlobalBounds>(Position(mcPos.x, mcPos.y - 2 * mcDim.height), Dimentions(mcDim));
                std::shared_ptr<GlobalBounds> frontalAura3 =
                    std::make_shared<GlobalBounds>(Position(mcPos.x, mcPos.y - 3 * mcDim.height), Dimentions(mcDim));
                std::shared_ptr<GlobalBounds> frontalAura4 =
                    std::make_shared<GlobalBounds>(Position(mcPos.x, mcPos.y - 4 * mcDim.height), Dimentions(mcDim));
                std::shared_ptr<GlobalBounds> frontalLeftAura1 = std::make_shared<GlobalBounds>(
                    Position(mcPos.x - mcDim.width, mcPos.y - mcDim.height), Dimentions(mcDim));
                std::shared_ptr<GlobalBounds> frontalLeftAura2 = std::make_shared<GlobalBounds>(
                    Position(mcPos.x - mcDim.width, mcPos.y - 2 * mcDim.height), Dimentions(mcDim));
                std::shared_ptr<GlobalBounds> frontalLeftAura3 = std::make_shared<GlobalBounds>(
                    Position(mcPos.x - mcDim.width, mcPos.y - 3 * mcDim.height), Dimentions(mcDim));
                std::shared_ptr<GlobalBounds> frontalLeftAura4 = std::make_shared<GlobalBounds>(
                    Position(mcPos.x - mcDim.width, mcPos.y - 4 * mcDim.height), Dimentions(mcDim));
                std::shared_ptr<GlobalBounds> frontalRightAura1 = std::make_shared<GlobalBounds>(
                    Position(mcPos.x + mcDim.width, mcPos.y - mcDim.height), Dimentions(mcDim));
                std::shared_ptr<GlobalBounds> frontalRightAura2 = std::make_shared<GlobalBounds>(
                    Position(mcPos.x + mcDim.width, mcPos.y - 2 * mcDim.height), Dimentions(mcDim));
                std::shared_ptr<GlobalBounds> frontalRightAura3 = std::make_shared<GlobalBounds>(
                    Position(mcPos.x + mcDim.width, mcPos.y - 3 * mcDim.height), Dimentions(mcDim));
                std::shared_ptr<GlobalBounds> frontalRightAura4 = std::make_shared<GlobalBounds>(
                    Position(mcPos.x + mcDim.width, mcPos.y - 4 * mcDim.height), Dimentions(mcDim));

                std::shared_ptr<GlobalBounds> leftAura =
                    std::make_shared<GlobalBounds>(Position(mcPos.x - mcDim.width, mcPos.y), Dimentions(mcDim));
                std::shared_ptr<GlobalBounds> rightAura =
                    std::make_shared<GlobalBounds>(Position(mcPos.x + mcDim.width, mcPos.y), Dimentions(mcDim));
                return {frontalAura1,      frontalAura2,      frontalAura3,      frontalAura4,     leftAura,
                        rightAura,         frontalLeftAura1,  frontalLeftAura2,  frontalLeftAura3, frontalLeftAura4,
                        frontalRightAura1, frontalRightAura2, frontalRightAura3, frontalRightAura4};
        }
};
} // namespace TH

#endif // TURBOHIKER_MAINCHARACTER_H
