//
// Created by JOHN CHRISTIAN CASTILLO on 7/18/2021.
//

#include "StaticHiker.h"

TH::StaticHiker::StaticHiker(const float& horizontalOffset)
{
        Position pos = Position((horizontalOffset), 0);
        Dimensions dim = Dimensions(0.222222f, 0.444444f);
        globalBounds = std::make_shared<GlobalBounds>(pos, dim);
        movementSpeed = 1;
}
TH::EntityTypes TH::StaticHiker::getType() const { return EntityTypes::staticHiker; }
TH::StaticHiker::StaticHiker(const TH::Position& pos)
{
        Position newPos = Position(pos.x, pos.y + 0.444444f);
        Dimensions dim = Dimensions(0.222222f, 0.444444f);
        globalBounds = std::make_shared<GlobalBounds>(newPos, dim);
        movementSpeed = 1;
}
