//
// Created by reed on 12.08.21.
//

#ifndef TURBOHIKER_SPEEDUP_H
#define TURBOHIKER_SPEEDUP_H


#include "PowerUp.h"

class SpeedUp: public PowerUp {
public:
    explicit SpeedUp(const float& horizontalOffset);
    EntityTypes getType() const override;

};


#endif//TURBOHIKER_SPEEDUP_H
