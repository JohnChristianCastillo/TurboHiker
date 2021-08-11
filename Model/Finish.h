//
// Created by reed on 11.08.21.
//

#ifndef TURBOHIKER_FINISH_H
#define TURBOHIKER_FINISH_H


#include "Entity.h"
class Finish: public Entity {
public:
    explicit Finish();
    EntityTypes getType() const override;
};


#endif//TURBOHIKER_FINISH_H
