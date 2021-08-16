//
// Created by reed on 12.08.21.
//

#ifndef TURBOHIKER_SPEEDUP_H
#define TURBOHIKER_SPEEDUP_H

#include "PowerUp.h"

namespace TH {
class SpeedUp : public PowerUp
{
public:
        /**
         * Instantiates A SpeedUp power up at a position + a random offset determined by the EntityMaker
         * @param horizontalOffset: A random offset determined by the EntityMaker
         */
        explicit SpeedUp(const float& horizontalOffset);

        /**
         * @return The type of this power up, here "invincibilityStar"
         */
        EntityTypes getType() const override;
};
} // namespace TH

#endif // TURBOHIKER_SPEEDUP_H
