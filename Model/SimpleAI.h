//
// Created by reed on 04.08.21.
//

#ifndef TURBOHIKER_SIMPLEAI_H
#define TURBOHIKER_SIMPLEAI_H

#include "EnemyHikers/Enemy.h"

class SimpleAI: public Enemy{
    // counts how many ticks it has been since the AI moved left or right
    int notMovingTicks{150};
public:
    /**
     * This AI moves UP towards the finish line by default
     * This only changes to LEFT or RIGHT depending on whether it has an enemy
     * to its left or to its right
     * @param enemyUp
     * @param enemyLeft
     * @param enemyRight
     * @param xOffset
     * @param yOffset
     */
    void randomMove(bool enemyUp, bool enemyLeft, bool enemyRight, bool enemyUpLeft, bool enemyUpRight, const float& xOffset, const float& yOffset){
        // go right
        if(enemyUpLeft and !enemyRight){
            globalBounds->position.x += std::abs(xOffset);
        }
        //go left
        else if(enemyUpRight and !enemyLeft){

            globalBounds->position.x -= std::abs(xOffset);
        }
        // enemy above not left and right
        else if(enemyUp and !enemyLeft and !enemyRight){
            std::shared_ptr<singleton::Random> random = singleton::Random::getInstance();
            int direction = random->intInInterval(0,1);
            // 0 is left 1 is right
            if(direction == 0){
                globalBounds->position.x -= std::abs(xOffset);
            }
            else{
                globalBounds->position.x += std::abs(xOffset);
            }
        }
        // default move is to move up;
        // but we don't do vertical movement on the ai JUST YET
        else{
            --notMovingTicks;
            if(notMovingTicks<=0){
                if(!enemyLeft){
                    globalBounds->position.x -= std::abs(xOffset);
                    notMovingTicks = 150;
                }
                else if(!enemyRight){
                    globalBounds->position.x += std::abs(xOffset);
                    notMovingTicks = 150;
                }
                //else is when there are both left and right enemy, if so we don't move
            }
        }
    }
    SimpleAI();
    EntityTypes getType() const override { return EntityTypes::staticHiker; }
    /**
     *
     * @return {UP-UP, UP-UP-UP, LEFT, RIGHT, UPLEFT, UPRIGHT}
     */
    std::vector<std::shared_ptr<GlobalBounds>> getLookAhead(){
        Position aiPos = globalBounds->position;
        Dimentions aiDim = globalBounds->dimentions;
        std::shared_ptr<GlobalBounds> frontalAura1 = std::make_shared<GlobalBounds>(Position(aiPos.x, aiPos.y-aiDim.height), Dimentions(aiDim));
        std::shared_ptr<GlobalBounds> frontalAura2 = std::make_shared<GlobalBounds>(Position(aiPos.x, aiPos.y-2*aiDim.height), Dimentions(aiDim));
        std::shared_ptr<GlobalBounds> frontalAura3 = std::make_shared<GlobalBounds>(Position(aiPos.x, aiPos.y-3*aiDim.height), Dimentions(aiDim));
        std::shared_ptr<GlobalBounds> leftAura = std::make_shared<GlobalBounds>(Position(aiPos.x-aiDim.width/2, aiPos.y), Dimentions(aiDim));
        std::shared_ptr<GlobalBounds> rightAura = std::make_shared<GlobalBounds>(Position(aiPos.x+aiDim.width/2, aiPos.y), Dimentions(aiDim));
        std::shared_ptr<GlobalBounds> upRightAura = std::make_shared<GlobalBounds>(Position(aiPos.x+aiDim.width/2, aiPos.y-aiDim.height), Dimentions(aiDim));
        std::shared_ptr<GlobalBounds> upLeftAura = std::make_shared<GlobalBounds>(Position(aiPos.x-aiDim.width/2, aiPos.y-aiDim.height), Dimentions(aiDim));
        return {frontalAura1, frontalAura2, frontalAura3, leftAura, rightAura, upLeftAura, upRightAura};
    }
};


#endif//TURBOHIKER_SIMPLEAI_H
