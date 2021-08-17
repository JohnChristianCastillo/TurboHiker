//
// Created by reed on 17.08.21.
//

#ifndef TURBOHIKER_LASERBEAM_H
#define TURBOHIKER_LASERBEAM_H

#include "PowerUp.h"
namespace TH {
class LaserBeam : public PowerUp
{
public:
        /**
         * @return The type of this power up, here "laserBeamPowerUp"
         */
        EntityTypes getType() const override;

        /**
         * Instantiates A LaserBeam power up at a position + a random offset determined by the EntityMaker
         * @param horizontalOffset: A random offset determined by the EntityMaker
         */
        explicit LaserBeam(const float& horizontalOffset);
};
} // namespace TH
#endif // TURBOHIKER_LASERBEAM_H
