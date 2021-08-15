//
// Created by reed on 15.08.21.
//

#include "InvincibilityStar.h"
EntityTypes InvincibilityStar::getType() const {
    return EntityTypes::invincibilityStar;
}
InvincibilityStar::InvincibilityStar(const float &horizontalOffset) {
    Position pos = Position((horizontalOffset), -1);
    Dimentions dim = Dimentions(0.222222f, 0.444444f);
    globalBounds = std::make_shared<GlobalBounds>(pos, dim);
    movementSpeed = 1;
}
