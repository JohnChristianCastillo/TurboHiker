//
// Created by reed on 17.08.21.
//

#ifndef TURBOHIKER_NUKE_H
#define TURBOHIKER_NUKE_H

#include "PowerUp.h"
namespace TH {
class Nuke : public PowerUp
{
public:
        /**
         * Instantiates A Nuke power up at a position + a random offset determined by the EntityMaker
         * @param horizontalOffset: A random offset determined by the EntityMaker
         */
        explicit Nuke(const float& horizontalOffset);

        /**
         * @return The type of this power up, here "nukePowerUp"
         */
        EntityTypes getType() const override;
};
} // namespace TH

#endif // TURBOHIKER_NUKE_H
