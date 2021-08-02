//
// Created by JOHN CHRISTIAN CASTILLO on 7/18/2021.
//

#ifndef TURBOHIKER_ENEMY_H
#define TURBOHIKER_ENEMY_H

#include "Entity.h"

class Enemy: public Entity{
protected:
    bool collided{false};

public:
    bool isCollided() const;
    void setCollided(bool collided);



};


#endif//TURBOHIKER_ENEMY_H
