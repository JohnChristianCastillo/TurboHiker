//
// Created by JOHN CHRISTIAN CASTILLO on 7/18/2021.
//

#include "Entity.h"
int Entity::getSkin() {
    if(skin == -1){
        std::shared_ptr<singleton::Random> random = singleton::Random::getInstance();
        skin = random->intInInterval(1,11);
        return skin;
    }
    else{
        return skin;
    }
}
float Entity::getSlowingFactor() const {
    return slowingFactor;
}


void Entity::setGlobalBounds(const std::shared_ptr<GlobalBounds> &globalBounds) {
    Entity::globalBounds = globalBounds;
}
