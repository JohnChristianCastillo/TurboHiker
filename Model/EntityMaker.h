//
// Created by JOHN CHRISTIAN CASTILLO on 7/18/2021.
//

#ifndef TURBOHIKER_ENTITYMAKER_H
#define TURBOHIKER_ENTITYMAKER_H

#include "../Singletons/Random.h"
#include "Background.h"
#include "Enemy.h"
#include "Finish.h"
#include "MainCharacter.h"
#include "PowerUps/PowerUp.h"
#include "PowerUps/SpeedUp.h"
#include "SimpleAI.h"
#include "StaticHiker.h"
#include <set>
#include <vector>

class EntityMaker {
public:
    std::shared_ptr<MainCharacter> generateMainCharacter(int lanes){

        return std::make_shared<MainCharacter>(MainCharacter{lanes});
    }
    std::shared_ptr<Finish> generateFinishLine(){

        return std::make_shared<Finish>();
    }

    std::shared_ptr<SimpleAI> generateAI(){
        return std::make_shared<SimpleAI>();
    }
    std::vector<std::shared_ptr<Enemy>> generateEnemies(){
        // assigns to which lane the enemy will go to:
        std::shared_ptr<singleton::Random> random = singleton::Random::getInstance();
        int enemiesToGenerate = random->intInInterval(0,4);
        std::vector<std::shared_ptr<Enemy>> returnEnemies{};
        std::set<int> set;
        while(set.size() != enemiesToGenerate){
            int randomOffset = random->intInInterval(0,6);
            set.insert(randomOffset);
        }
        for(auto randomOffset: set){
            float randomOffsetOffset = random->floatInInterval(-0.2, 0.2);
            std::shared_ptr<Enemy> tempEnemy = std::make_shared<StaticHiker>(static_cast<float>(randomOffset)+randomOffsetOffset);
            float tempPosX = tempEnemy->getGlobalBounds()->position.x;
            float tempWidth = tempEnemy->getGlobalBounds()->dimentions.width;
            if(tempPosX + tempWidth/2 >= 6 or tempPosX - tempWidth/2 <=0){
                tempEnemy = std::make_shared<StaticHiker>(static_cast<float>(randomOffset));
            }
            returnEnemies.push_back(tempEnemy);
            //std::cout << "Generated enemy#" <<  i++ << ": " << tempEnemy->getGlobalBounds()->position.x << std::endl;

        }
        return returnEnemies;
    }

    std::vector<std::shared_ptr<PowerUp>> generatePowerUp(){
        // assigns to which lane the enemy will go to:
        std::shared_ptr<singleton::Random> random = singleton::Random::getInstance();
        int powerUpsToGenerate = random->intInInterval(0,4);
        std::vector<std::shared_ptr<PowerUp>> returnPowerUp{};
        std::set<int> set;
        while(set.size() != powerUpsToGenerate){
            int randomOffset = random->intInInterval(0,6);
            set.insert(randomOffset);
        }
        for(auto randomOffset: set){
            float randomOffsetOffset = random->floatInInterval(-0.2, 0.2);
            std::shared_ptr<PowerUp> powerUp = std::make_shared<SpeedUp>(static_cast<float>(randomOffset)+randomOffsetOffset);
            float tempPosX = powerUp->getGlobalBounds()->position.x;
            float tempWidth = powerUp->getGlobalBounds()->dimentions.width;
            if(tempPosX + tempWidth/2 >= 6 or tempPosX - tempWidth/2 <=0){
                powerUp = std::make_shared<SpeedUp>(static_cast<float>(randomOffset));
            }
            returnPowerUp.push_back(powerUp);
            //std::cout << "Generated enemy#" <<  i++ << ": " << tempEnemy->getGlobalBounds()->position.x << std::endl;

        }
        return returnPowerUp;
    }

    std::vector<std::shared_ptr<Background>> generateBackground(){
        return {std::make_shared<Background>(0),
                std::make_shared<Background>(-1),
                std::make_shared<Background>(-2)};
    }

};


#endif//TURBOHIKER_ENTITYMAKER_H
