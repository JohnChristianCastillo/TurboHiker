//
// Created by reed on 17.08.21.
//

#ifndef TURBOHIKER_SUMMONENEMY_H
#define TURBOHIKER_SUMMONENEMY_H

#include "PowerUp.h"

namespace TH {
class SummonEnemy : public PowerUp
{
public:
        /**
         * Instantiates A SummonEnemy power up at a position + a random offset determined by the EntityMaker
         * @param horizontalOffset: A random offset determined by the EntityMaker
         */
        explicit SummonEnemy(const float& horizontalOffset);

        /**
         * @return The type of this power up, here "summonEnemy"
         */
        EntityTypes getType() const override;
};
} // namespace TH

#endif // TURBOHIKER_SUMMONENEMY_H
