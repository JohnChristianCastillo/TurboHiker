//
// Created by JOHN CHRISTIAN CASTILLO on 7/18/2021.
//

#ifndef TURBOHIKER_ENTITY_H
#define TURBOHIKER_ENTITY_H

#include "../HelperDataTypes.h"
#include "../Singletons/Random.h"
#include "iostream"

namespace TH {
class Entity
{
protected:
        int skin{-1}; // texture used
        std::shared_ptr<GlobalBounds> globalBounds;
        float movementSpeed; // used to determine the entities velocity
        float slowingFactor{1};
        bool slowed{false};
        bool sped{false};

public:
        void setGlobalBounds(const std::shared_ptr<GlobalBounds>& globalBounds);
        float getSlowingFactor() const;
        void reduceSlowingEffect(float sf)
        {
                if (slowingFactor >= 1) {
                        slowingFactor = 1;
                } else {
                        slowingFactor = sf;
                }
        }
        void reduceSpeedBoostEffect(float sf)
        {
                if (slowingFactor <= 1) {
                        slowingFactor = 1;
                } else {
                        slowingFactor = sf;
                }
        }
        int getSkin();

        /**
         * slow player down by a factor of 60%
         * this gradually returns to its original speed
         */
        void slowDown()
        {
                slowed = true;
                if (slowingFactor > 2) {
                        slowingFactor -= 0.9;
                } else {
                        slowingFactor = 0.01;
                }
        }
        bool isSlowed()
        {
                if (slowingFactor == 1) {
                        slowed = false;
                }
                return slowed;
        }
        bool isSped()
        {
                if (slowingFactor == 1) {
                        sped = false;
                }
                return sped;
        }
        void speedUp()
        {
                sped = true;
                if (slowingFactor <= 1) {
                        slowingFactor += 1;
                } else {
                        slowingFactor = 2;
                }
                // std::cout << "slowing factor: " << slowingFactor << std::endl;
        }
        virtual EntityTypes getType() const = 0;
        float getMovementSpeed() const { return movementSpeed; };
        std::shared_ptr<GlobalBounds> getGlobalBounds() const { return globalBounds; }
        void setPosition(float x, float y)
        {
                globalBounds->position.x = x;
                globalBounds->position.y = y;
        }

        virtual void move(const float& xOffset, const float& yOffset)
        {
                if (!(globalBounds->position.x + xOffset > 6 or globalBounds->position.x + xOffset < 0)) {
                        globalBounds->position.x += xOffset;
                        globalBounds->position.y += yOffset;
                }
        }
};
} // namespace TH

#endif // TURBOHIKER_ENTITY_H
