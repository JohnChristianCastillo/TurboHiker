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

        float scareCooldown{0};
        bool invincible{false};

        float invincibleDuration{0};

public:
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
        /**
         * Instantiates a MainCharacter object at the center of the screen, taking into account how many lanes there are
         * @param lanes: lanes of the game
         */
        explicit MainCharacter(int lanes);

        /**
         * @return True if the player is scaring players, False otherwise
         */
        bool isScaringEnemy() const;

        /**
         * sets scareEnemy value to _scareEnemy
         * @param scareEnemy
         */
        void setScareEnemy(bool _scareEnemy);

        /**
         * sets yelling value to _yelling
         * @param _yelling
         */
        void setYelling(bool _yelling);

        /**
         * Applies a cool down time to the scaring ability of the player
         */
        void resetScareCoolDown();

        /**
         * Reduces the cool down of the ability of the player to scare enemy hikers
         */
        void decrementScareCoolDown();

        /**
         * @return The remaining cool down left before the player can scare hikers again
         */
        float getScareCoolDown() const;

        /**
         * @return True if the player is invincible, False otherwise
         */
        bool isInvincible();

        /**
         * Turns the player invincible for a short duration
         */
        void startInvincibility();

        /**
         * Reduces the duration of the invincibility
         * @param decr: amount by which the invincibility will be reduced
         */
        void decreaseInvincibilityDuration(const float& decr);

        /**
         * @return The duration of the players invincibility status
         */
        const float& getInvincibilityDuration() const;

        /**
         * @return The type of this entity, in this case "MainCharacter"
         */
        EntityTypes getType() const override;
};
} // namespace TH

#endif // TURBOHIKER_MAINCHARACTER_H
