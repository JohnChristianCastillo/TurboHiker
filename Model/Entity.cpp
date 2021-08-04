//
// Created by JOHN CHRISTIAN CASTILLO on 7/18/2021.
//

#include "Entity.h"
#include "../Singletons/Random.h"
int Entity::getSkin() {
    if(skin == -1){
        std::shared_ptr<singleton::Random> random = singleton::Random::getInstance();
        skin = random->intInInterval(1,12);
        return skin;
    }
    else{
        return skin;
    }
}
float Entity::getSlowingFactor() const {
    return slowingFactor;
}
void Entity::setSlowingFactor(float slowingFactor) {
    if(slowingFactor >=1){
        Entity::slowingFactor = 1;
    }
    else{
        Entity::slowingFactor = slowingFactor;
    }
}
