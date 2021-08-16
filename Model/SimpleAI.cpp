//
// Created by reed on 04.08.21.
//

#include "SimpleAI.h"
TH::SimpleAI::SimpleAI()
{
        /// todo: 8 divided by lanes doesnt really make sense;
        Position pos = Position(2.f, 5.5f);
        Dimentions dim = Dimentions(0.222222f, 0.444444f);
        globalBounds = std::make_shared<GlobalBounds>(pos, dim);
        movementSpeed = 5;
}
