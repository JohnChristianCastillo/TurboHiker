//
// Created by reed on 14.08.21.
//

#include "LeftToRightHiker.h"
TH::LeftToRightHiker::LeftToRightHiker(const float& horizontalOffset)
{
        std::shared_ptr<singleton::Random> random = singleton::Random::getInstance();
        moveLeft = random->intInInterval(0, 1);
        Position pos = Position((1.5f + 1.5f * horizontalOffset), -0.5);
        Dimensions dim = Dimensions(0.222222f, 0.444444f);
        globalBounds = std::make_shared<GlobalBounds>(pos, dim);
        movementSpeed = 0.5;
}
TH::EntityTypes TH::LeftToRightHiker::getType() const { return EntityTypes::leftToRightHiker; }
void TH::LeftToRightHiker::move(const float& xOffset, const float& yOffset)
{
        globalBounds->position.y += yOffset;
        // we identify first if this is the first or the second left or right hiker
        // identifying first(left) hiker
        if (globalBounds->position.x + globalBounds->dimensions.width / 2 <= 3) {
                if (moveLeft) {
                        // and we haven't gotten off screen
                        if (globalBounds->position.x - globalBounds->dimensions.width / 2 > 0) {
                                globalBounds->position.x -= xOffset;
                        }
                        // if we're offscreen
                        else {
                                moveLeft = false;
                                globalBounds->position.x += xOffset;
                        }
                        return;
                }
                if (!moveLeft) {
                        // and we haven't gotten past half the screen
                        if (globalBounds->position.x + globalBounds->dimensions.width / 2 + xOffset > 3) {
                                globalBounds->position.x -= xOffset;
                                moveLeft = true;
                        }
                        // if we're past half the screen
                        else {
                                globalBounds->position.x += xOffset;
                        }
                }
        }
        // second (rightHiker)
        else {
                if (moveLeft) {
                        // if next position is past midline
                        if (globalBounds->position.x - globalBounds->dimensions.width / 2 - xOffset < 3) {
                                globalBounds->position.x += xOffset;
                                moveLeft = false;
                        }
                        // if we're offscreen
                        else {
                                globalBounds->position.x -= xOffset;
                        }
                        return;
                }
                if (!moveLeft) {
                        // if next position is past the screen
                        if (globalBounds->position.x + globalBounds->dimensions.width / 2 + xOffset > 6) {
                                globalBounds->position.x -= xOffset;
                                moveLeft = true;
                        }
                        // if we're past half the screen
                        else {
                                globalBounds->position.x += xOffset;
                        }
                }
        }
}