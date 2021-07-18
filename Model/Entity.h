//
// Created by JOHN CHRISTIAN CASTILLO on 7/18/2021.
//

#ifndef TURBOHIKER_ENTITY_H
#define TURBOHIKER_ENTITY_H

#include "../HelperDataTypes.h"

class Entity {
protected:
    std::shared_ptr<Coordinates> coordinates{};
    float movementSpeed; //used to determine the entities velocity

public:
    virtual EntityTypes getType() const = 0;
    virtual float getMovementSpeed() const = 0;
    std::shared_ptr<Coordinates> getCoordinates() const{
        return coordinates;
    }

    void move(float x, float y){
        coordinates->lowLeft.first += x;
        coordinates->lowLeft.second += y;
        coordinates->upRight.first += x;
        coordinates->upRight.second += y;
    };
};


#endif//TURBOHIKER_ENTITY_H
