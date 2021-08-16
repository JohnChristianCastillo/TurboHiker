//
// Created by reed on 04.08.21.
//

#include "SimpleAI.h"
TH::SimpleAI::SimpleAI()
{
        /// todo: 8 divided by lanes doesnt really make sense;
        Position pos = Position(2.f, 5.5f);
        Dimensions dim = Dimensions(0.222222f, 0.444444f);
        globalBounds = std::make_shared<GlobalBounds>(pos, dim);
        movementSpeed = 5;
}
void TH::SimpleAI::randomMove(bool enemyUp, bool enemyLeft, bool enemyRight, bool enemyUpLeft, bool enemyUpRight,
                              const float& xOffset, const float& yOffset)
{
        // go right
        if (enemyUpLeft and !enemyRight) {
                globalBounds->position.x += std::abs(xOffset);
        }
        // go left
        else if (enemyUpRight and !enemyLeft) {

                globalBounds->position.x -= std::abs(xOffset);
        }
        // enemy above not left and right
        else if (enemyUp and !enemyLeft and !enemyRight) {
                std::shared_ptr<singleton::Random> random = singleton::Random::getInstance();
                int direction = random->intInInterval(0, 1);
                // 0 is left 1 is right
                if (direction == 0) {
                        globalBounds->position.x -= std::abs(xOffset);
                } else {
                        globalBounds->position.x += std::abs(xOffset);
                }
        }
        // default move is to move up;
        // but we don't do vertical movement on the ai JUST YET
        else {
                --notMovingTicks;
                if (notMovingTicks <= 0) {
                        if (!enemyLeft) {
                                globalBounds->position.x -= std::abs(xOffset);
                                notMovingTicks = 150;
                        } else if (!enemyRight) {
                                globalBounds->position.x += std::abs(xOffset);
                                notMovingTicks = 150;
                        }
                        // else is when there are both left and right enemy, if so we don't move
                }
        }
}
std::vector<std::shared_ptr<TH::GlobalBounds>> TH::SimpleAI::getLookAhead()
{
        Position aiPos = globalBounds->position;
        Dimensions aiDim = globalBounds->dimensions;
        std::shared_ptr<GlobalBounds> frontalAura1 =
            std::make_shared<GlobalBounds>(Position(aiPos.x, aiPos.y - aiDim.height), Dimensions(aiDim));
        std::shared_ptr<GlobalBounds> frontalAura2 =
            std::make_shared<GlobalBounds>(Position(aiPos.x, aiPos.y - 2 * aiDim.height), Dimensions(aiDim));
        std::shared_ptr<GlobalBounds> frontalAura3 =
            std::make_shared<GlobalBounds>(Position(aiPos.x, aiPos.y - 3 * aiDim.height), Dimensions(aiDim));
        std::shared_ptr<GlobalBounds> leftAura =
            std::make_shared<GlobalBounds>(Position(aiPos.x - aiDim.width / 2, aiPos.y), Dimensions(aiDim));
        std::shared_ptr<GlobalBounds> rightAura =
            std::make_shared<GlobalBounds>(Position(aiPos.x + aiDim.width / 2, aiPos.y), Dimensions(aiDim));
        std::shared_ptr<GlobalBounds> upRightAura = std::make_shared<GlobalBounds>(
            Position(aiPos.x + aiDim.width / 2, aiPos.y - aiDim.height), Dimensions(aiDim));
        std::shared_ptr<GlobalBounds> upLeftAura = std::make_shared<GlobalBounds>(
            Position(aiPos.x - aiDim.width / 2, aiPos.y - aiDim.height), Dimensions(aiDim));
        return {frontalAura1, frontalAura2, frontalAura3, leftAura, rightAura, upLeftAura, upRightAura};
}
