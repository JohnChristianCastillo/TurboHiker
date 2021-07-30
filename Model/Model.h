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
    explicit Model(float frameLimit):fps(frameLimit){
        entityFactory = std::make_shared<EntityMaker>();

        enemies = std::move(generateEnemies());
        mainCharacter = generateMC();
    }

    float getFps() const;


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

    void moveRight(const float elapsedTime){
        playerMove.x += mainCharacter->getMovementSpeed()*elapsedTime;
        //std::shared_ptr<Coordinates> newCoords = model->getMainCharacter()->moveRight(elapsedTime*10.f);
        //std::shared_ptr<singleton::Transformation> trans = singleton::Transformation::getInstance();
        //std::tuple<float,float> x = trans->modelToView(newCoords);

    }
    void moveLeft(const float elapsedTime){
        playerMove.x -= mainCharacter->getMovementSpeed()*elapsedTime;

        //float move = model->getMainCharacter()->getMovementSpeed()/model->getFps();
        //if(model->getMainCharacter()->getCoordinates()->lowLeft.first + move >= 0){
        //    model->getMainCharacter()->move(-move, 0);
        //}
        //std::cout << "Left" << std::endl;
    }

    /**
     * loop over all the enemy entities and move them
     * at the same time, clear undisplayed enemies from the vector
     */
    void moveEnemies(const float elapsedTime){
        //for(int i = model->getEnemies().size()-1; i >= 0; --i){
        //    model->getEnemies().at(i)->move(0, model->getMainCharacter()->getMovementSpeed()/model->getFps());
        //    if(model->getEnemies().at(i)->getCoordinates()->lowLeft.second > 8.f){
//
        //        model->getEnemies().erase(model->getEnemies().begin()+i);
        //    }
        //}
        backgroundMove.y += 10*elapsedTime;
    }

    void moveMC(){
        mainCharacter->move(playerMove.x, playerMove.y);
    }

    void collisionControl(){

        for(const std::shared_ptr<Enemy>& wall: enemies){
            std::shared_ptr<GlobalBounds> playerBounds = mainCharacter->getGlobalBounds();
            std::shared_ptr<GlobalBounds> wallBounds = wall->getGlobalBounds();

            nextPosition = playerBounds;
            nextPosition->left += (playerMove.x - backgroundMove.x) * 10;
            nextPosition->top += (playerMove.y - backgroundMove.y) * 10;

            if(wallBounds->intersects<float>(nextPosition)){
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
                if (playerBounds->top < wallBounds->top &&
                playerBounds->top + playerBounds->dimentions.height < wallBounds->top + wallBounds->dimentions.height &&
                playerBounds->left < wallBounds->left + wallBounds->dimentions.width &&
                playerBounds->left + playerBounds->dimentions.width > wallBounds->left) {
                    playerMove.y = 0.f;
                    // bottom of player set to top of wall
                    mainCharacter->setPosition(playerBounds->left, wallBounds->top - playerBounds->dimentions.height);
                }
                // Player Top collision
                else if (playerBounds->top > wallBounds->top &&
                playerBounds->top + playerBounds->dimentions.height > wallBounds->top + wallBounds->dimentions.height &&
                playerBounds->left < wallBounds->left + wallBounds->dimentions.width &&
                playerBounds->left + playerBounds->dimentions.width > wallBounds->left) {
                    playerMove.y = 0.f;
                    // top of player set to bottom of wall                 plus cause y goes down
                    mainCharacter->setPosition(playerBounds->left, wallBounds->top + wallBounds->dimentions.height);
                }

                // Player right collision
                else if (playerBounds->left < wallBounds->left &&
                playerBounds->left + playerBounds->dimentions.width < wallBounds->left + wallBounds->dimentions.width &&
                playerBounds->top < wallBounds->top + wallBounds->dimentions.height &&
                playerBounds->top + playerBounds->dimentions.height > wallBounds->top) {
                    playerMove.x = 0.f;
                    mainCharacter->setPosition(wallBounds->left - playerBounds->dimentions.width, playerBounds->top);
                }
                // Player Left collision
                else if (playerBounds->left > wallBounds->left &&
                playerBounds->left + playerBounds->dimentions.width > wallBounds->left + wallBounds->dimentions.width &&
                playerBounds->top < wallBounds->top + wallBounds->dimentions.height &&
                playerBounds->top + playerBounds->dimentions.height > wallBounds->top) {
                    playerMove.x = 0.f;
                    mainCharacter->setPosition(wallBounds->left + wallBounds->dimentions.width, playerBounds->top);
                }
            }
        }
    }


};


#endif//TURBOHIKER_MODEL_H
