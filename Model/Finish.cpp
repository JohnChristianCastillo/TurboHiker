//
// Created by reed on 11.08.21.
//

#include "Finish.h"
TH::Finish::Finish()
{
        Position pos = Position(0.f, 0.f);
        Dimensions dim = Dimensions(12.f, 0.444444f);
        globalBounds = std::make_shared<GlobalBounds>(pos, dim);
        movementSpeed = 1;
}
TH::EntityTypes TH::Finish::getType() const { return EntityTypes::finishLine; }
