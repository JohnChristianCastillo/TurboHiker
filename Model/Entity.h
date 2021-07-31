//
// Created by JOHN CHRISTIAN CASTILLO on 7/18/2021.
//

#ifndef TURBOHIKER_ENTITY_H
#define TURBOHIKER_ENTITY_H

#include "../HelperDataTypes.h"

class Entity {
protected:
    std::shared_ptr<GlobalBounds> globalBounds;
    float movementSpeed; //used to determine the entities velocity

public:
    virtual EntityTypes getType() const = 0;
    float getMovementSpeed() const{
            return movementSpeed;
    };
    std::shared_ptr<GlobalBounds> getGlobalBounds() const{
        return globalBounds;
    }
    void setPosition(float x, float y){
        globalBounds->position.x = x;
        globalBounds->position.y = y;
    }
    void move(float offsetX, float offsetY){
        globalBounds->position.x += offsetX;
        globalBounds->position.y += offsetY;   }
    /*
    void move(float x, float y){
        coordinates->lowLeft.first += x;
        coordinates->lowLeft.second += y;
        coordinates->upRight.first += x;
        coordinates->upRight.second += y;
    };*/

    /**
     * Keep in mind that we are working with rectangle objects
     * @param nextPosition
     * @return
     */
    template<typename type>
    bool intersects(const std::shared_ptr<GlobalBounds>& nextPosition) const{
        type left = globalBounds->position.x - globalBounds->dimentions.width/2;
        type top = globalBounds->position.y + globalBounds->dimentions.height/2;

        type nextLeft = nextPosition->position.x - nextPosition->dimentions.width/2;
        type nextTop = nextPosition->position.y + nextPosition->dimentions.height/2;

        // Compute the min and max x and y of the the entity we're in
        type thisMinX = std::min(left, static_cast<type>(left + globalBounds->dimentions.width));
        type thisMaxX = std::max(left, static_cast<type>(left + globalBounds->dimentions.width));
        type thisMinY = std::min(top, static_cast<type>(top + globalBounds->dimentions.height));
        type thisMaxY = std::min(top, static_cast<type>(top + globalBounds->dimentions.height));

        // Compute the min and max x and y of the the next position we're in
        type r2MinX = std::min(nextLeft, static_cast<type>(nextLeft + nextPosition->dimentions.width));
        type r2MaxX = std::max(nextLeft, static_cast<type>(nextLeft + nextPosition->dimentions.width));
        type r2MinY = std::min(nextTop, static_cast<type>(nextTop + nextPosition->dimentions.height));
        type r2MaxY = std::max(nextTop, static_cast<type>(nextTop + nextPosition->dimentions.height));

        // Compute the intersection boundaries
        type interLeft   = std::max(thisMinX, r2MinX);
        type interTop    = std::max(thisMinY, r2MinY);
        type interRight  = std::min(thisMaxX, r2MaxX);
        type interBottom = std::min(thisMaxY, r2MaxY);

        return (interLeft < interRight) && (interTop < interBottom);
    }
};


#endif//TURBOHIKER_ENTITY_H
