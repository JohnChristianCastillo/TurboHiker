//
// Created by JOHN CHRISTIAN CASTILLO on 7/18/2021.
//

#ifndef TURBOHIKER_STATICHIKER_H
#define TURBOHIKER_STATICHIKER_H

#include "Enemy.h"

class StaticHiker: public Enemy {
public:
    /**
     * Initializes a static hiker given a horizontal offset
     * @param horizontalOffset
     */
    explicit StaticHiker(const int& horizontalOffset);
    EntityTypes getType() const override { return EntityTypes::staticHiker; }
};


#endif//TURBOHIKER_STATICHIKER_H
