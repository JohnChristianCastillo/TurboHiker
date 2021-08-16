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

public:
        /**
         * Instantiates a simple AI
         */
        SimpleAI();

        /**
         * This AI moves UP towards the finish line by default
         * This only changes to LEFT or RIGHT depending on whether it has an enemy
         * to its left or to its right
         * @param enemyUp
         * @param enemyLeft
         * @param enemyRight
         * @param xOffset
         * @param yOffset
         */
        void randomMove(bool enemyUp, bool enemyLeft, bool enemyRight, bool enemyUpLeft, bool enemyUpRight,
                        const float& xOffset, const float& yOffset);

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
