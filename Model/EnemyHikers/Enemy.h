//
// Created by JOHN CHRISTIAN CASTILLO on 7/18/2021.
//

#ifndef TURBOHIKER_ENEMY_H
#define TURBOHIKER_ENEMY_H

#include "../Entity.h"

class Enemy: public Entity{
protected:
    // counts how many times it has been yelled at
    int yellPoints;
    bool collided{false};
    bool steerRandolmy{false};

public:
    bool isSteerRandolmy() const;
    void setSteerRandolmy(bool steerRandolmy);

public:
    void addYellPoints(){
        yellPoints++;
    }
    bool exceededScareThreshold(){
        std::shared_ptr<singleton::Random> rand = singleton::Random::getInstance();
        int randomOffset = rand->intInInterval(0,10);
        if(randomOffset + yellPoints>= 700){
            return true;
        }
        yellPoints += randomOffset;
        return false;
    }



};


#endif//TURBOHIKER_ENEMY_H
