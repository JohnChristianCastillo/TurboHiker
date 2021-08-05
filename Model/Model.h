//
// Created by JOHN CHRISTIAN CASTILLO on 7/18/2021.
//

#ifndef TURBOHIKER_MODEL_H
#define TURBOHIKER_MODEL_H

#include "../Observers/LiveScoring.h"
#include "Enemy.h"
#include "EntityMaker.h"
#include "MainCharacter.h"
#include <iostream>
#include <utility>
#include <vector>

class Model {
    int lanes{4};
    float fps;
private:
    std::shared_ptr<EntityMaker> entityFactory;
    std::shared_ptr<MainCharacter> mainCharacter;
    std::shared_ptr<SimpleAI> simpleAi;
    std::shared_ptr<LiveScoring> scoringSystem;
    std::vector<std::shared_ptr<Enemy>> enemies;
    std::vector<std::shared_ptr<Background>> backgrounds;

    Move playerMove{};
    Move backgroundMove{};
    std::shared_ptr<GlobalBounds> nextPosition;

    // simpleAI vars
    bool enemyUp{false};
    bool enemyLeft{false};
    bool enemyRight{false};
    bool enemyUpLeft{false};
    bool enemyUpRight{false};
public:
    const Move &getPlayerMove() const;
    void setPlayerMoveX(const float &moveX);
    void setPlayerMoveY(const float &moveY);
    const Move &getBackgroundMove() const;
    void setBackgroundMoveY(const float &moveY);
    const std::shared_ptr<LiveScoring> &getScoringSystem() const;
    explicit Model(float frameLimit, const std::weak_ptr<LiveScoring>&  scoringObserver):fps(frameLimit), scoringSystem(std::move(scoringObserver))
    {
        entityFactory = std::make_shared<EntityMaker>();

        enemies = std::move(generateEnemies());
        mainCharacter = generateMC();
        simpleAi = generateAI();
        backgrounds = generateBackground();
        scoringSystem = std::make_shared<LiveScoring>();
    }

    float getFps() const;


    std::shared_ptr<MainCharacter> getMainCharacter() const{
        return mainCharacter;
    }
    std::shared_ptr<SimpleAI> getSimpleAI() const{
        return simpleAi;
    }
    std::vector<std::shared_ptr<Background>> getBackgrounds() const{
        return backgrounds;
    }
    std::vector<std::shared_ptr<Enemy>> getEnemies(){
        if(enemies.empty()){
            enemies = entityFactory->generateEnemies();
        }
        return enemies;
    }

    std::shared_ptr<MainCharacter> generateMC(){
        return entityFactory->generateMainCharacter(lanes);
    };
    std::shared_ptr<SimpleAI> generateAI(){
        return entityFactory->generateAI();
    };

    std::vector<std::shared_ptr<Background>> generateBackground(){
        return entityFactory->generateBackground();
    }
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

    void resetMoves(){
        playerMove = {};
        backgroundMove = {};
    }

    void moveMC(){
        mainCharacter->move(playerMove.x, playerMove.y);
    }

    void moveBackground(){
        Position bg1Pos = backgrounds[0]->getGlobalBounds()->position;
        Position bg2Pos = backgrounds[1]->getGlobalBounds()->position;
        Position mcPos = mainCharacter->getGlobalBounds()->position;
        if (bg1Pos.y > mcPos.y) {
            backgrounds[2]->setPosition(bg1Pos.x, bg1Pos.y);
            backgrounds[0]->setPosition(bg1Pos.x,bg1Pos.y - backgrounds[0]->getGlobalBounds()->dimentions.height * 2);
        } else if (bg2Pos.y > mcPos.y) {
            backgrounds[2]->setPosition(bg2Pos.x, bg2Pos.y);
            backgrounds[1]->setPosition(bg2Pos.x,bg2Pos.y - backgrounds[1]->getGlobalBounds()->dimentions.height * 2);
        }
        for(const auto& bg: backgrounds){
            if(mainCharacter->isSlowed()){
                bg->move(backgroundMove.x, backgroundMove.y*mainCharacter->getSlowingFactor());

            }
            else{
                bg->move(backgroundMove.x, backgroundMove.y);
            }
        }
        if(mainCharacter->isSlowed()) {
             mainCharacter->setSlowingFactor(mainCharacter->getSlowingFactor()+0.01f);
        }

    }
    void moveEnemies(){
        // generate new enemies if last generated enemy is past half the screen;
        if(enemies.back()->getGlobalBounds()->position.y >= 4.f){
            generateEnemies();
        }
        for(int i = enemies.size()-1; i>=0; --i){
            std::shared_ptr<Enemy> enemy = enemies[i];
            if(enemy->isSteerRandolmy()) {
                steerRandomly(enemy);
            }
            else if(enemy->getGlobalBounds()->position.y>=9.f){
                //remove enemies outside of scope
                enemies.erase(enemies.begin()+i);
            }
            else{
                // advance ai at normal speed even if mc is slowed;
                //simpleAi->move(0, -backgroundMove.y*mainCharacter->getSlowingFactor());
                if(enemy->isSlowed()){
                    enemy->move(backgroundMove.x, backgroundMove.y*mainCharacter->getSlowingFactor()*enemy->getSlowingFactor());
                    enemy->setSlowingFactor(enemy->getSlowingFactor()+0.1f);
                }
                else{
                    enemy->move(backgroundMove.x, backgroundMove.y*mainCharacter->getSlowingFactor());
                }
            }
        }
    }

    void screenCollisionControl(){
        Position mcPos = mainCharacter->getGlobalBounds()->position;
        Dimentions mcDim = mainCharacter->getGlobalBounds()->dimentions;
        /// Window collision control
        /// left collision
        if (mcPos.x - (mcDim.width / 2) <= 0) {
            mainCharacter->setPosition(mcDim.width / 2, mainCharacter->getGlobalBounds()->position.y);
        }
        /// right collision
        if (mcPos.x + (mcDim.width/2) >= 6.f) {
            mainCharacter->setPosition(6.f - (mcDim.width/2), mcPos.y);
        }

        /// Window collision control
        Position aiPos = simpleAi->getGlobalBounds()->position;
        Dimentions aiDim = simpleAi->getGlobalBounds()->dimentions;
        /// left collision
        if (aiPos.x - (aiDim.width / 2) <= 0) {
            simpleAi->setPosition(aiDim.width / 2, simpleAi->getGlobalBounds()->position.y);
        }
        /// right collision
        if (aiPos.x + (aiDim.width/2) >= 6.f) {
            simpleAi->setPosition(6.f - (aiDim.width/2), aiPos.y);
        }
    }

    void steerRandomly(const std::shared_ptr<Enemy>& enemy){
        Move enemyMove = backgroundMove;
        std::shared_ptr<singleton::Random> random = singleton::Random::getInstance();
        std::vector<Input> direction{Input::LEFT, Input::RIGHT};
        int index = random->intInInterval(0,1);
        switch(direction[index]){
            case LEFT:
                enemyMove.y = 0;
                if(enemyMove.x == 0){
                    enemyMove.x -= 0.4f;
                }
                break;
            case RIGHT:
                enemyMove.y = 0;
                if(enemyMove.x == 0){
                    enemyMove.x += 0.4f;
                }
                break;
            default:
                break;
        }
        enemy->move(enemyMove.x, enemyMove.y);
        enemy->setSteerRandolmy(false);
    }
    /**
     * This function checks collision between:
     * 1: The main character and (the enemy spawned together with the simple AI)
     * 2: The Simple AI and (the enemy spawned together with the main character)
     *
     * This combination is necessary to achieve only looping once through all the spawned enemy entities
     */
    void collisionControl(){

        for(int i = enemies.size()-1; i>=0; --i){
            // first initialize the next position of our player;
            std::shared_ptr<GlobalBounds> playerBounds = mainCharacter->getGlobalBounds();
            nextPosition = std::make_shared<GlobalBounds>(*playerBounds);
            nextPosition->position.x += (playerMove.x - backgroundMove.x);
            nextPosition->position.y += (playerMove.y - backgroundMove.y);

            // then we initialize the lookahead our AI has;

            std::vector<std::shared_ptr<GlobalBounds>> simpleAILookAhead = simpleAi->getLookAhead();
            for(int j = 0; j<=2; ++j){
                // check whether the three frontal lookahead intersects with either the spawned enemy or the MC if so warn our AI
                if(simpleAILookAhead[j]->intersects<float>(enemies[i]->getGlobalBounds()) or simpleAILookAhead[j]->intersects<float>(nextPosition)){
                    enemyUp = true;
                    break;
                }
            }
            if(simpleAILookAhead[3]->intersects<float>(enemies[i]->getGlobalBounds()) or simpleAILookAhead[3]->intersects<float>(nextPosition)){
                enemyLeft = true;
            }
            if(simpleAILookAhead[4]->intersects<float>(enemies[i]->getGlobalBounds()) or simpleAILookAhead[4]->intersects<float>(nextPosition)){
                enemyRight = true;
            }
            //up left
            if(simpleAILookAhead[5]->intersects<float>(enemies[i]->getGlobalBounds()) or simpleAILookAhead[5]->intersects<float>(nextPosition)){
                enemyUpLeft = true;
            }
            //up right
            if(simpleAILookAhead[6]->intersects<float>(enemies[i]->getGlobalBounds()) or simpleAILookAhead[6]->intersects<float>(nextPosition)){
                enemyUpRight = true;
            }

            // we need to know if our player is yelling and an enemy sprite in in its vicinity if so we need to deduct points
            if(mainCharacter->isYelling()){
                std::vector<std::shared_ptr<GlobalBounds>> mcAuras = mainCharacter->getAura();
                for(const auto& aura:mcAuras){
                    if(enemies[i]->getGlobalBounds()->intersects<float>(aura)){
                        scoringSystem->hikerOffended();
                        enemies[i]->slowDown();
                    }
                }
                mainCharacter->setYelling(false);
            }
            // we need to know if our MC is scaring off enemy players, if so we add scarePoints to the player
            // This in turn causes the enemy to panic steer
            // this scarePoint has a threshold and once exceeded it can throw off the enemy
            if(mainCharacter->isScaringEnemy()){
                std::vector<std::shared_ptr<GlobalBounds>> mcAuras = mainCharacter->getAura();
                bool enemyDeleted{false};
                for(const auto& aura:mcAuras){
                    if(enemies[i]->getGlobalBounds()->intersects<float>(aura)){
                        if(enemies[i]->exceededScareThreshold()){
                            enemies.erase(enemies.begin()+i);
                            scoringSystem->hikerThrownOff();
                            enemyDeleted = true;
                            break;
                        }
                        else{
                            // if it hasn't exceeded the threshold yet, we will steer the enemy randomly
                            enemies[i]->setSteerRandolmy(true);
                            scoringSystem->hikerOffended();

                        }
                    }
                }
                mainCharacter->setScareEnemy(false);
                // if enemy is thrown off we need to skip the collision control
                if(enemyDeleted){
                    continue;
                }
            }

            if(enemies[i]->getGlobalBounds()->intersects<float>(nextPosition)){
                // if we collided we want to penalize our player by slowing it down and subtracting points
                scoringSystem->crashed();
                mainCharacter->slowDown();
                enemies.erase(enemies.begin()+i);
            }

        }
        simpleAi->randomMove(enemyUp, enemyLeft, enemyRight, enemyUpLeft, enemyUpRight, (playerMove.x+backgroundMove.y), 0);
        enemyLeft = false;
        enemyRight = false;
        enemyUp = false;
        enemyUpLeft = false;
        enemyUpRight = false;
        /*
        for(const std::shared_ptr<Enemy>& wall: enemies){
            std::shared_ptr<GlobalBounds> playerBounds = mainCharacter->getGlobalBounds();
            std::shared_ptr<GlobalBounds> wallBounds = wall->getGlobalBounds();

            nextPosition = std::make_shared<GlobalBounds>(*playerBounds);
            nextPosition->position.x += (playerMove.x - backgroundMove.x);
            nextPosition->position.y += (playerMove.y - backgroundMove.y);

            std::cout << "wall #" << counter++ << ": " << wallBounds->position.x <<" "<< wallBounds->position.y << std::endl;
            if(wall->intersects<float>(nextPosition)){

                std::cout << "Collision" << std::endl;
                /// possible solution1: set playerMove x and y to 0
                /// possible solution2:  first construct left and right collision,
                ///                     bottom-top is simillar but inverted
                //   player            wall
                //  ________          ________
                // |        |        |        |
                // |        |        |        |
                // |        |        |        |
                // |________|        |________|

                // Player Bottom collision
                float playerTop = playerBounds->position.y + playerBounds->dimentions.height/2;
                float wallTop = wallBounds->position.y + wallBounds->dimentions.height/2;
                float playerLeft = playerBounds->position.x - playerBounds->dimentions.width/2;
                float wallLeft = wallBounds->position.x - wallBounds->dimentions.width/2;

                if (playerTop < wallTop &&
                playerTop + playerBounds->dimentions.height < wallTop + wallBounds->dimentions.height &&
                playerLeft < wallLeft + wallBounds->dimentions.width &&
                playerLeft + playerBounds->dimentions.width > wallLeft) {
                    playerMove.y = 0.f;
                    // bottom of player set to top of wall
                    //mainCharacter->setPosition(playerLeft, wallTop - playerBounds->dimentions.height);
                    mainCharacter->setPosition(playerLeft, wallTop - playerBounds->dimentions.height);
                }
                // Player Top collision
                else if (playerTop > wallTop &&
                playerTop + playerBounds->dimentions.height > wallTop + wallBounds->dimentions.height &&
                playerLeft < wallLeft + wallBounds->dimentions.width &&
                playerLeft + playerBounds->dimentions.width > wallLeft) {
                    playerMove.y = 0.f;
                    // top of player set to bottom of wall                 plus cause y goes down
                   // mainCharacter->setPosition(playerLeft, wallTop + wallBounds->dimentions.height);
                    mainCharacter->setPosition(playerLeft, wallTop + wallBounds->dimentions.height);
                }

                // Player right collision
                else if (playerLeft < wallLeft &&
                playerLeft + playerBounds->dimentions.width < wallLeft + wallBounds->dimentions.width &&
                playerTop < wallTop + wallBounds->dimentions.height &&
                playerTop + playerBounds->dimentions.height > wallTop) {
                    playerMove.x = 0.f;
                    //mainCharacter->setPosition(wallLeft - playerBounds->dimentions.width, playerTop);
                    mainCharacter->setPosition(wallLeft - playerBounds->dimentions.width, playerTop);
                }
                // Player Left collision
                else if (playerLeft > wallLeft &&
                playerLeft + playerBounds->dimentions.width > wallLeft + wallBounds->dimentions.width &&
                playerTop < wallTop + wallBounds->dimentions.height &&
                playerTop + playerBounds->dimentions.height > wallTop) {
                    playerMove.x = 0.f;
                    //mainCharacter->setPosition(wallLeft + wallBounds->dimentions.width, playerTop);
                    mainCharacter->setPosition(wallLeft + wallBounds->dimentions.width, playerTop);
                }
            }
        }*/
    }


};


#endif//TURBOHIKER_MODEL_H
