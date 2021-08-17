//
// Created by reed on 17.08.21.
//

#include "SummonEnemy.h"
TH::SummonEnemy::SummonEnemy(const float& horizontalOffset)
{
        Position pos = Position((horizontalOffset), -1);
        Dimensions dim = Dimensions(0.222222f, 0.444444f);
        globalBounds = std::make_shared<GlobalBounds>(pos, dim);
        movementSpeed = 1;
}
TH::EntityTypes TH::SummonEnemy::getType() const { return EntityTypes::summonEnemy; }
