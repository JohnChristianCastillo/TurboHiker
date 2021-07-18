//
// Created by JOHN CHRISTIAN CASTILLO on 7/18/2021.
//

#ifndef TURBOHIKER_ENTITYMAKER_H
#define TURBOHIKER_ENTITYMAKER_H

#include "../Singletons/Random.h"
#include "Enemy.h"
#include "MainCharacter.h"
#include "StaticHiker.h"
#include <map>
#include <vector>

class EntityMaker {
public:
    std::shared_ptr<MainCharacter> generateMainCharacter(){

        return std::make_shared<MainCharacter>(MainCharacter{});
    }

    std::vector<std::shared_ptr<Enemy>> generateEnemies(){
        std::map<int,int> randomOffsetMapping{};
        std::shared_ptr<Random> random = Random::getInstance();
        int enemiesToGenerate = random->intInInterval(0,4);
        std::vector<std::shared_ptr<Enemy>> returnEnemies{};
        for(int i = 1; i <= enemiesToGenerate; ++i){
            bool notFound{true};
            while(notFound){
                int randomOffset = random->intInInterval(0,6);
                //if not in mapping
                if(randomOffsetMapping.find(randomOffset) == randomOffsetMapping.end()){
                    std::shared_ptr<Enemy> tempEnemy = std::make_shared<StaticHiker>(randomOffset);
                    returnEnemies.push_back(tempEnemy);
                    notFound = false;
                }
            }
        }
        return returnEnemies;
    }

};


#endif//TURBOHIKER_ENTITYMAKER_H
