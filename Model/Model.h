//
// Created by JOHN CHRISTIAN CASTILLO on 7/18/2021.
//

#ifndef TURBOHIKER_MODEL_H
#define TURBOHIKER_MODEL_H

#include "Enemy.h"
#include "MainCharacter.h"
#include "EntityMaker.h"
#include <vector>

class Model {
    int lanes{4};
    std::shared_ptr<EntityMaker> entityFactory;
    std::shared_ptr<MainCharacter> mainCharacter;
    std::vector<std::shared_ptr<Enemy>> enemies;

public:
    std::shared_ptr<MainCharacter> getMainCharacter(){
        return mainCharacter;
    }
    std::vector<std::shared_ptr<Enemy>> getEnemies(){
        if(enemies.empty()){
            enemies = entityFactory->generateEnemies();
        }
        return enemies;
    }
    std::vector<std::shared_ptr<Enemy>> generateEnemies(){
        std::vector<std::shared_ptr<Enemy>> generatedEnemies = entityFactory->generateEnemies();
        for(const std::shared_ptr<Enemy>& enemy: generatedEnemies){
            enemies.push_back(enemy);
        }
        return enemies;
    }
};


#endif//TURBOHIKER_MODEL_H
