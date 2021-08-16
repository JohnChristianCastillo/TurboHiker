//
// Created by reed on 14.08.21.
//

#ifndef TURBOHIKER_LEFTTORIGHTHIKER_H
#define TURBOHIKER_LEFTTORIGHTHIKER_H

#include "Enemy.h"

namespace TH {
class LeftToRightHiker : public Enemy
{
        bool moveLeft;

public:
        /**
         * Initializes a static hiker given a horizontal offset
         * @param horizontalOffset
         */
        explicit LeftToRightHiker(const float& horizontalOffset);
        EntityTypes getType() const override { return leftToRightHiker; }
        void move(const float& xOffset, const float& yOffset) override
        {
                globalBounds->position.y += yOffset;
                // we identify first if this is the first or the second left or right hiker
                // identifying first(left) hiker
                if (globalBounds->position.x + globalBounds->dimentions.width / 2 <= 3) {
                        if (moveLeft) {
                                // and we haven't gotten off screen
                                if (globalBounds->position.x - globalBounds->dimentions.width / 2 > 0) {
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
                                if (globalBounds->position.x + globalBounds->dimentions.width / 2 + xOffset > 3) {
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
                                if (globalBounds->position.x - globalBounds->dimentions.width / 2 - xOffset < 3) {
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
                                if (globalBounds->position.x + globalBounds->dimentions.width / 2 + xOffset > 6) {
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
};
} // namespace TH

#endif // TURBOHIKER_LEFTTORIGHTHIKER_H
