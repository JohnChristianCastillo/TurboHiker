//
// Created by JOHN CHRISTIAN CASTILLO on 7/18/2021.
//

#ifndef TURBOHIKER_STATICHIKER_H
#define TURBOHIKER_STATICHIKER_H

#include "Enemy.h"

namespace TH {
class StaticHiker : public Enemy
{
public:
        /**
         * Initializes a static hiker given a horizontal offset
         * @param horizontalOffset
         */
        explicit StaticHiker(const float& horizontalOffset);

        /**
         * Spawns a static hiker at given position
         * @param pos: position on which the hiker will be spawned
         */
        explicit StaticHiker(const Position& pos);

        /**
         * @return The type of this hiker, here "staticHiker"
         */
        EntityTypes getType() const override;
};
} // namespace TH

#endif // TURBOHIKER_STATICHIKER_H
