//
// Created by reed on 31.07.21.
//

#ifndef TURBOHIKER_BACKGROUND_H
#define TURBOHIKER_BACKGROUND_H
#include "Entity.h"

class Background: public Entity{
public:
    explicit Background(float centerOffset){
        Position pos = Position(0.f, 1.f+centerOffset*8.f);
        Dimentions dim = Dimentions(6.f, 8.f);
        globalBounds = std::make_shared<GlobalBounds>(pos, dim);
        movementSpeed = 1;
    }
    EntityTypes getType() const override{
        return EntityTypes::background;
    }
};


#endif//TURBOHIKER_BACKGROUND_H
