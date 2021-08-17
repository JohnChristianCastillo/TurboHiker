//
// Created by reed on 17.08.21.
//

#include "Nuke.h"
TH::EntityTypes TH::Nuke::getType() const { return EntityTypes::nukePowerUp; }
TH::Nuke::Nuke(const float& horizontalOffset)
{
        Position pos = Position((horizontalOffset), -1);
        Dimensions dim = Dimensions(0.222222f, 0.444444f);
        globalBounds = std::make_shared<GlobalBounds>(pos, dim);
        movementSpeed = 1;
}
