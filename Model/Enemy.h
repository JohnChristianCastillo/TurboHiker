//
// Created by JOHN CHRISTIAN CASTILLO on 7/18/2021.
//

#ifndef TURBOHIKER_ENEMY_H
#define TURBOHIKER_ENEMY_H

#include "Entity.h"

class Enemy: public Entity{
protected:
    // counts how many times it has been scared
    int scarePoints;
    bool collided{false};
    bool steerRandolmy{false};

public:
    bool isSteerRandolmy() const;
    void setSteerRandolmy(bool steerRandolmy);

public:
    bool isCollided() const;
    void setCollided(bool collided);
    bool exceededScareThreshold() const{
        if(scarePoints >= 10){
            return true;
        }
        return false;
    }
    void increaseScarePoints(){
        scarePoints++;
    }



};


#endif//TURBOHIKER_ENEMY_H
