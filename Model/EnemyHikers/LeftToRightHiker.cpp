//
// Created by reed on 14.08.21.
//

#include "LeftToRightHiker.h"
TH::LeftToRightHiker::LeftToRightHiker(const float& horizontalOffset)
{
        std::shared_ptr<singleton::Random> random = singleton::Random::getInstance();
        moveLeft = random->intInInterval(0, 1);
        Position pos = Position((1.5f + 1.5f * horizontalOffset), -0.5);
        Dimentions dim = Dimentions(0.222222f, 0.444444f);
        globalBounds = std::make_shared<GlobalBounds>(pos, dim);
        movementSpeed = 0.5;
}
