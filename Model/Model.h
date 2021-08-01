//
// Created by JOHN CHRISTIAN CASTILLO on 7/18/2021.
//

#ifndef TURBOHIKER_MODEL_H
#define TURBOHIKER_MODEL_H

#include "Enemy.h"
#include "EntityMaker.h"
#include "MainCharacter.h"
#include <iostream>
#include <vector>

class Model {
    int lanes{4};
    float fps;
private:
    std::shared_ptr<EntityMaker> entityFactory;
    std::shared_ptr<MainCharacter> mainCharacter;
    std::vector<std::shared_ptr<Enemy>> enemies;
    std::vector<std::shared_ptr<Background>> backgrounds;

    Move playerMove{};
    Move backgroundMove{};
    std::shared_ptr<GlobalBounds> nextPosition;
public:
    const Move &getPlayerMove() const;
    void setPlayerMoveX(const float &moveX);
    void setPlayerMoveY(const float &moveY);
    const Move &getBackgroundMove() const;
    void setBackgroundMoveY(const float &moveY);

public:
    Model(float frameLimit):fps(frameLimit)
    {
        entityFactory = std::make_shared<EntityMaker>();

        enemies = std::move(generateEnemies());
        mainCharacter = generateMC();
        backgrounds = generateBackground();
    }

    float getFps() const;


    std::shared_ptr<MainCharacter> getMainCharacter() const{
        return mainCharacter;
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
            bg->move(backgroundMove.x, backgroundMove.y);
        }
    }
    void moveEnemies(){
        // generate new enemies if last generated enemy is past half the screen;
        if(enemies.back()->getGlobalBounds()->position.y >= 4.f){
            generateEnemies();
        }
        for(int i = enemies.size()-1; i>=0; --i){
            std::shared_ptr<Enemy> enemy = enemies[i];
            if(enemy->isCollided()) continue;
            else if(enemy->getGlobalBounds()->position.y>=9.f){
                //remove enemies outside of scope
                enemies.erase(enemies.begin()+i);
            }
            else{
                enemy->move(backgroundMove.x, backgroundMove.y);
            }
        }
    }

    void screenCollisionControl(){
        Position mcPos = mainCharacter->getGlobalBounds()->position;
        Dimentions mcDim = mainCharacter->getGlobalBounds()->dimentions;
        /// Window collision control
        /// left collision
        if (mcPos.x - mcDim.width / 2 < 0) {
            mainCharacter->setPosition(mcDim.width / 2, mainCharacter->getGlobalBounds()->position.y);
        }
        /// right collision
        if (mcPos.x + mcDim.width > 6.f) {
            mainCharacter->setPosition(6.f - mcDim.width, mcPos.y);
        }
    }

    void collisionControl(){
        int counter = 1;

        for(const std::shared_ptr<Enemy>& wall: enemies){
            std::shared_ptr<GlobalBounds> playerBounds = mainCharacter->getGlobalBounds();
            std::shared_ptr<GlobalBounds> wallBounds = wall->getGlobalBounds();

            nextPosition = std::make_shared<GlobalBounds>(*playerBounds);
            nextPosition->position.x += (playerMove.x - backgroundMove.x) * 10;
            nextPosition->position.y += (playerMove.y - backgroundMove.y) * 10;

            std::cout << "wall" << counter << ": " << wallBounds->position.x <<" "<< wallBounds->position.y << std::endl;
            std::cout << "player: " << nextPosition->position.x <<" "<< nextPosition->position.y << std::endl;
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
                    mainCharacter->setPosition(playerLeft, wallTop - playerBounds->dimentions.height);
                }
                // Player Top collision
                else if (playerTop > wallTop &&
                playerTop + playerBounds->dimentions.height > wallTop + wallBounds->dimentions.height &&
                playerLeft < wallLeft + wallBounds->dimentions.width &&
                playerLeft + playerBounds->dimentions.width > wallLeft) {
                    playerMove.y = 0.f;
                    // top of player set to bottom of wall                 plus cause y goes down
                    mainCharacter->setPosition(playerLeft, wallTop + wallBounds->dimentions.height);
                }

                // Player right collision
                else if (playerLeft < wallLeft &&
                playerLeft + playerBounds->dimentions.width < wallLeft + wallBounds->dimentions.width &&
                playerTop < wallTop + wallBounds->dimentions.height &&
                playerTop + playerBounds->dimentions.height > wallTop) {
                    playerMove.x = 0.f;
                    mainCharacter->setPosition(wallLeft - playerBounds->dimentions.width, playerTop);
                }
                // Player Left collision
                else if (playerLeft > wallLeft &&
                playerLeft + playerBounds->dimentions.width > wallLeft + wallBounds->dimentions.width &&
                playerTop < wallTop + wallBounds->dimentions.height &&
                playerTop + playerBounds->dimentions.height > wallTop) {
                    playerMove.x = 0.f;
                    mainCharacter->setPosition(wallLeft + wallBounds->dimentions.width, playerTop);
                }
            }
        }
    }


};


#endif//TURBOHIKER_MODEL_H
