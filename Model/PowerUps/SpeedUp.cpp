//
// Created by reed on 12.08.21.
//

#include "SpeedUp.h"
EntityTypes SpeedUp::getType() const {
    return EntityTypes::speedUp;
}
SpeedUp::SpeedUp(const float &horizontalOffset) {
    Position pos = Position((horizontalOffset), 0.5);
    Dimentions dim = Dimentions(0.222222f, 0.444444f);
    globalBounds = std::make_shared<GlobalBounds>(pos, dim);
    movementSpeed = 5;
}
