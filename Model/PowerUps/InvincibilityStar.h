//
// Created by reed on 15.08.21.
//

#ifndef TURBOHIKER_INVINCIBILITYSTAR_H
#define TURBOHIKER_INVINCIBILITYSTAR_H


#include "PowerUp.h"
class InvincibilityStar: public PowerUp {

public:
    EntityTypes getType() const override;
    explicit InvincibilityStar(const float& horizontalOffset);
};


#endif//TURBOHIKER_INVINCIBILITYSTAR_H
