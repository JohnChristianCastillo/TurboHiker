//
// Created by reed on 12.08.21.
//

#include "SpeedUp.h"
TH::EntityTypes TH::SpeedUp::getType() const { return EntityTypes::speedUp; }
TH::SpeedUp::SpeedUp(const float& horizontalOffset)
{
        Position pos = Position((horizontalOffset), -1);
        Dimentions dim = Dimentions(0.222222f, 0.444444f);
        globalBounds = std::make_shared<GlobalBounds>(pos, dim);
        movementSpeed = 1;
}
