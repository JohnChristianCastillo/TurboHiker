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
    Model(){
        entityFactory = std::make_shared<EntityMaker>();

        generateEnemies();
        generateMC();
    }
    std::shared_ptr<MainCharacter> getMainCharacter(){
        return mainCharacter;
    }
    std::vector<std::shared_ptr<Enemy>> getEnemies(){
        if(enemies.empty()){
            enemies = entityFactory->generateEnemies();
        }
        return enemies;
    }

    std::shared_ptr<MainCharacter> generateMC(){
            return entityFactory->generateMainCharacter();
    };

    /**
     * Generates enemies of random types spawning them at the top part of the screen
     * @return A vector of generated enemies
     */
    std::vector<std::shared_ptr<Enemy>> generateEnemies(){
        // we can't just assign the generated enemies directly to our enemies container since enemies can be
        // not empty
        std::vector<std::shared_ptr<Enemy>> generatedEnemies = entityFactory->generateEnemies();
        for(std::shared_ptr<Enemy>& enemy: generatedEnemies){
            enemies.push_back(std::move(enemy));
        }
        return enemies;
    }
};


#endif//TURBOHIKER_MODEL_H
