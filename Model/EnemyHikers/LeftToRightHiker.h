//
// Created by reed on 14.08.21.
//

#ifndef TURBOHIKER_LEFTTORIGHTHIKER_H
#define TURBOHIKER_LEFTTORIGHTHIKER_H

#include "Enemy.h"

namespace TH {
class LeftToRightHiker : public Enemy
{
        bool moveLeft; // used to determine which side this entity is supposed to travel to
public:
        /**
         * Initializes a static hiker given a horizontal offset
         * @param horizontalOffset
         */
        explicit LeftToRightHiker(const float& horizontalOffset);

        /**
         * @return The type of this hiker, here "leftToRightHiker"
         */
        EntityTypes getType() const override;

        /**
         * Moves the entity by adding/subtracting the offset to its coordinates
         * @param xOffset: offset of x coordinate
         * @param yOffset: offset of y coordinate
         */
        void move(const float& xOffset, const float& yOffset) override;
};
} // namespace TH

#endif // TURBOHIKER_LEFTTORIGHTHIKER_H
