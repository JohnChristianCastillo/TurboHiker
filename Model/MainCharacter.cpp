//
// Created by JOHN CHRISTIAN CASTILLO on 7/18/2021.
//

#include "MainCharacter.h"
MainCharacter::MainCharacter(int lanes) {
    /// todo: 8 divided by lanes doesnt really make sense;
    Position pos = Position(6.f/static_cast<float>(lanes)*2, 8.f/static_cast<float>(lanes)*2);
    Dimentions dim = Dimentions(6.f/static_cast<float>(lanes), 8.f/static_cast<float>(lanes));
    globalBounds = std::make_shared<GlobalBounds>(pos, dim);
    movementSpeed = 10;
}
