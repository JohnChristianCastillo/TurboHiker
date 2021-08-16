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
         * @return The type of this hiker, here "staticHiker"
         */
        EntityTypes getType() const override;
};
} // namespace TH

#endif // TURBOHIKER_STATICHIKER_H
