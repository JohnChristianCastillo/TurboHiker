//
// Created by JOHN CHRISTIAN CASTILLO on 7/18/2021.
//

#ifndef TURBOHIKER_ENTITY_H
#define TURBOHIKER_ENTITY_H

#include "../HelperDataTypes.h"
#include "../Singletons/Random.h"
#include "iostream"
class Entity {
protected:
    int skin{-1}; //texture used
    std::shared_ptr<GlobalBounds> globalBounds;
    float movementSpeed; //used to determine the entities velocity
    float slowingFactor{1};

public:
    int getSkin();

    /**
     * slow player down by a factor of 60%
     * this gradually returns to its original speed
     */
    void slowDown(){
        slowingFactor = 0.01;
    }
    void speedUp(){
        slowingFactor = 2;
    }
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
        globalBounds->position.y += offsetY*slowingFactor;
        if(slowingFactor < 1){
            slowingFactor += 0.01;
            std::cout << "I am slowe by: " << slowingFactor << std::endl;
        }
        else if(slowingFactor < 0){
            slowingFactor -= 0.1;
        }
    }
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

        // calculate leftX and topY of current
        type left = globalBounds->position.x - globalBounds->dimentions.width/2;
        type top = globalBounds->position.y - globalBounds->dimentions.height/2;

        // calculate leftX and topY of other object
        type nextLeft = nextPosition->position.x - nextPosition->dimentions.width/2;
        type nextTop = nextPosition->position.y - nextPosition->dimentions.height/2;

        // Compute the min and max x and y of the the entity we're in

        type thisMinX = left;
        type thisMaxX = static_cast<type>(left + globalBounds->dimentions.width);
        type thisMinY = top;
        type thisMaxY = static_cast<type>(top + globalBounds->dimentions.height);

        // Compute the min and max x and y of the the next position we're in
        type r2MinX = nextLeft;
        type r2MaxX = static_cast<type>(nextLeft + nextPosition->dimentions.width);
        type r2MinY = nextTop;
        type r2MaxY = static_cast<type>(nextTop + nextPosition->dimentions.height);

        // Compute the intersection boundaries
        type interLeft   = std::max(thisMinX, r2MinX);
        type interTop    = std::max(thisMinY, r2MinY);
        type interRight  = std::min(thisMaxX, r2MaxX);
        type interBottom = std::min(thisMaxY, r2MaxY);

        bool b =(interLeft < interRight) && (interTop < interBottom);
        return b;

    }
};


#endif//TURBOHIKER_ENTITY_H
