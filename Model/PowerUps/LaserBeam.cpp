//
// Created by reed on 17.08.21.
//

#include "LaserBeam.h"

TH::EntityTypes TH::LaserBeam::getType() const { return EntityTypes::laserBeamPowerUp; }
TH::LaserBeam::LaserBeam(const float& horizontalOffset)
{
        Position pos = Position((horizontalOffset), -1);
        Dimensions dim = Dimensions(0.222222f, 0.444444f);
        globalBounds = std::make_shared<GlobalBounds>(pos, dim);
        movementSpeed = 1;
}