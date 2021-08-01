//
// Created by JOHN CHRISTIAN CASTILLO on 7/18/2021.
//

#include "StaticHiker.h"
StaticHiker::StaticHiker(const int &horizontalOffset) {
    /// todo: 8 divided by lanes doesnt really make sense;
    Position pos = Position(static_cast<float>(horizontalOffset), 0);
    Dimentions dim = Dimentions(0.222222f, 0.444444f);
    globalBounds = std::make_shared<GlobalBounds>(pos, dim);
    movementSpeed = 5;
}
