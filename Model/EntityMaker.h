//
// Created by JOHN CHRISTIAN CASTILLO on 7/18/2021.
//

#ifndef TURBOHIKER_ENTITYMAKER_H
#define TURBOHIKER_ENTITYMAKER_H

#include "../Singletons/Random.h"
#include "Background.h"
#include "Enemy.h"
#include "MainCharacter.h"
#include "StaticHiker.h"
#include <map>
#include <vector>

class EntityMaker {
public:
    std::shared_ptr<MainCharacter> generateMainCharacter(int lanes){

        return std::make_shared<MainCharacter>(MainCharacter{lanes});
    }

    std::vector<std::shared_ptr<Enemy>> generateEnemies(){
        // assigns to which lane the enemy will go to:
        std::map<int,int> randomOffsetMapping{};
        std::shared_ptr<singleton::Random> random = singleton::Random::getInstance();
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

    std::vector<std::shared_ptr<Background>> generateBackground(){
        return {std::make_shared<Background>(0),
                std::make_shared<Background>(-1),
                std::make_shared<Background>(-2)};
    }

};


#endif//TURBOHIKER_ENTITYMAKER_H
