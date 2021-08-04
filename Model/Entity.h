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
    float getSlowingFactor() const;
    void setSlowingFactor(float slowingFactor);

protected:
    bool slowed{false};

public:
    int getSkin();

    /**
     * slow player down by a factor of 60%
     * this gradually returns to its original speed
     */
    void slowDown(){
        slowed = true;
        slowingFactor = 0.01;
    }
    bool isSlowed(){
        if(slowingFactor == 1){
            slowed = false;
        }
        return slowed;
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

    virtual void move(const float& xOffset, const float& yOffset){

        globalBounds->position.x += xOffset;
        globalBounds->position.y += yOffset;
    }


};


#endif//TURBOHIKER_ENTITY_H
