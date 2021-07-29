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
    std::shared_ptr<GlobalBounds> getGlobalBounds() const{
        float width = coordinates->upRight.first - coordinates->lowLeft.first;
        float height = coordinates->upRight.second - coordinates->lowLeft.second;

        return std::make_shared<GlobalBounds>(coordinates->lowLeft.first, coordinates->upRight.second, Dimentions(width, height));
    }
    void setPosition(float x, float y){
        float width = coordinates->upRight.first - coordinates->lowLeft.first;
        float height = coordinates->upRight.second - coordinates->lowLeft.second;
        std::pair<float, float> lowLeft = std::make_pair(x, y-height);
        std::pair<float, float> upRight = std::make_pair(x+width, y);

        coordinates = std::make_shared<Coordinates>(lowLeft, upRight);
    }
    void move(float offsetX, float offsetY){
        this->setPosition(this->coordinates->lowLeft.first + offsetX,
                          this->coordinates->lowLeft.second + offsetY);
    }
    /*
    void move(float x, float y){
        coordinates->lowLeft.first += x;
        coordinates->lowLeft.second += y;
        coordinates->upRight.first += x;
        coordinates->upRight.second += y;
    };*/
};


#endif//TURBOHIKER_ENTITY_H
