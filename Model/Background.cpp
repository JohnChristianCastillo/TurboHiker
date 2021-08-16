//
// Created by reed on 31.07.21.
//

#include "Background.h"
TH::Background::Background(float centerOffset)
{
        Position pos = Position(0.f, 1.f + centerOffset * 8.f);
        Dimensions dim = Dimensions(6.f, 8.f);
        globalBounds = std::make_shared<GlobalBounds>(pos, dim);
        movementSpeed = 1;
}