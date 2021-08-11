//
// Created by reed on 11.08.21.
//

#include "Finish.h"
Finish::Finish() {
    Position pos = Position(0.f, 0.f);
    Dimentions dim = Dimentions(12.f, 0.444444f);
    globalBounds = std::make_shared<GlobalBounds>(pos, dim);
    movementSpeed = 1;


}
EntityTypes Finish::getType() const {
    return EntityTypes::FinishLine;
}
