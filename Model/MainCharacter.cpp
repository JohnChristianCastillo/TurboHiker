//
// Created by JOHN CHRISTIAN CASTILLO on 7/18/2021.
//

#include "MainCharacter.h"
MainCharacter::MainCharacter() {
    coordinates = std::make_shared<Coordinates>(std::make_pair(3.11f, 4.f), std::make_pair(3.f, 3.f));
    movementSpeed = 10;
}
