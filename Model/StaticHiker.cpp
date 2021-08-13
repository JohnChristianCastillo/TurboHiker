//
// Created by JOHN CHRISTIAN CASTILLO on 7/18/2021.
//

#include "StaticHiker.h"
StaticHiker::StaticHiker(const float &horizontalOffset) {
    Position pos = Position((horizontalOffset), 0);
    Dimentions dim = Dimentions(0.222222f, 0.444444f);
    globalBounds = std::make_shared<GlobalBounds>(pos, dim);
    movementSpeed = 5;
}
