//
// Created by JOHN CHRISTIAN CASTILLO on 7/18/2021.
//

#include "Entity.h"
#include "../Singletons/Random.h"
int Entity::getSkin() {
    if(skin == -1){
        std::shared_ptr<Random> random = Random::getInstance();
        skin = random->intInInterval(1,12);
        return skin;
    }
    else{
        return skin;
    }
}
