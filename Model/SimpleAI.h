//
// Created by reed on 04.08.21.
//

#ifndef TURBOHIKER_SIMPLEAI_H
#define TURBOHIKER_SIMPLEAI_H

#include "EnemyHikers/Enemy.h"

namespace TH {
class SimpleAI : public Enemy
{
        int notMovingTicks{150}; // counts how many ticks it has been since the AI moved left or right
        // simpleAI variables
        bool enemyUp{false};
        bool enemyLeft{false};
        bool enemyRight{false};
        bool enemyUpLeft{false};
        bool enemyUpRight{false};

public:
        /**
         * Instantiates a simple AI
         */
        explicit SimpleAI(const float& horizontalOffset);

        /**
         * Sets the value of enemyUp to _enemyUp
         * @param _enemyUp
         */
        void setEnemyUp(bool _enemyUp);

        /**
         * Sets the value of enemyLeft to _enemyLeft
         * @param _enemyLeft
         */
        void setEnemyLeft(bool _enemyLeft);

        /**
         * Sets the value of enemyRight to _enemyRight
         * @param _enemyRight
         */
        void setEnemyRight(bool _enemyRight);

        /**
         * Sets the value of enemyUpLeft to _enemyUpLeft
         * @param _enemyUpLeft
         */
        void setEnemyUpLeft(bool _enemyUpLeft);

        /**
         * Sets the value of enemyUpRight to _enemyUpRight
         * @param _enemyUpRight
         */
        void setEnemyUpRight(bool _enemyUpRight);

        /**
         * Resets the value of all boolean lookahead indicators to false
         */
        void resetLookAhead();

        /**
         * This AI moves UP towards the finish line by default
         * This only changes to LEFT or RIGHT depending on whether it has an enemy
         * to its left or to its right
         * @param xOffset
         * @param yOffset
         */
        void randomMove(const float& xOffset, const float& yOffset);

        /**
         * @return The type of this entity, in this cae "staticHiker"
         */
        EntityTypes getType() const override { return EntityTypes::staticHiker; }

        /**
         * returns the lookaheads of this AI
         * @return {UP-UP, UP-UP-UP, LEFT, RIGHT, UPLEFT, UPRIGHT}
         */
        std::vector<std::shared_ptr<GlobalBounds>> getLookAhead();
};
} // namespace TH

#endif // TURBOHIKER_SIMPLEAI_H
