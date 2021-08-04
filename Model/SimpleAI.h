//
// Created by reed on 04.08.21.
//

#ifndef TURBOHIKER_SIMPLEAI_H
#define TURBOHIKER_SIMPLEAI_H

#include "Enemy.h"

class SimpleAI: public Enemy{
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
    void randomMove(bool enemyUp, bool enemyLeft, bool enemyRight, const float& xOffset, const float& yOffset){
        // enemy above not left and right
        if(enemyUp and !enemyLeft and !enemyRight){
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
        // no enemy left but enemy right
        else if(enemyUp and !enemyLeft){
            globalBounds->position.x -= std::abs(xOffset);
        }
        // no enemy right but enemy left
        else if(enemyUp and !enemyRight){
            globalBounds->position.x += std::abs(xOffset);
        }
        // default move is to move up;
        // but we don't do vertical movement on the ai JUST YET
        else{
        }
    }
    SimpleAI();
    EntityTypes getType() const override { return EntityTypes::staticHiker; }
    /**
     *
     * @return {UP-UP, UP-UP-UP, LEFT, RIGHT}
     */
    std::vector<std::shared_ptr<GlobalBounds>> getLookAhead(){
        Position aiPos = globalBounds->position;
        Dimentions aiDim = globalBounds->dimentions;
        std::shared_ptr<GlobalBounds> frontalAura1 = std::make_shared<GlobalBounds>(Position(aiPos.x, aiPos.y-aiDim.height), Dimentions(aiDim));
        std::shared_ptr<GlobalBounds> frontalAura2 = std::make_shared<GlobalBounds>(Position(aiPos.x, aiPos.y-2*aiDim.height), Dimentions(aiDim));
        std::shared_ptr<GlobalBounds> frontalAura3 = std::make_shared<GlobalBounds>(Position(aiPos.x, aiPos.y-3*aiDim.height), Dimentions(aiDim));
        std::shared_ptr<GlobalBounds> leftAura = std::make_shared<GlobalBounds>(Position(aiPos.x-aiDim.width/2, aiPos.y), Dimentions(aiDim));
        std::shared_ptr<GlobalBounds> rightAura = std::make_shared<GlobalBounds>(Position(aiPos.x+aiDim.width/2, aiPos.y), Dimentions(aiDim));
        return {frontalAura1, frontalAura2, frontalAura3, leftAura, rightAura};
    }
};


#endif//TURBOHIKER_SIMPLEAI_H
