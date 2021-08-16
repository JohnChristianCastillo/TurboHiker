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
        int skin{-1};                               // texture used
        std::shared_ptr<GlobalBounds> globalBounds; // global bounds of this entity
        float movementSpeed;                        // used to determine the entities' velocity
        float slowingFactor{1};                     // factor by which the entity is slowed
        bool slowed{false};                         // variable indicating if the entity is slowed
        bool sped{false};                           // variable indicating if the entity is sped

public:
        /**
         * A pure virtual function returning the correct type of the entity that has inherited from this class
         * @return The type of the entity
         */
        virtual EntityTypes getType() const = 0;

        /**
         * @return The factor by which this entity is slowed by
         */
        float getSlowingFactor() const;

        /**
         * Reduce the slowing effect received by this entity
         * @param sf: slowing factor
         */
        void reduceSlowingEffect(float sf);

        /**
         * Reduce the speed effect received by this entity
         * @param sf: slowing factor
         */
        void reduceSpeedBoostEffect(float sf);

        /**
         * Sets the boolean variable "sped" to true and increases the speed of this entity
         */
        void speedUp();

        /**
         * slow player down by a factor of 60%
         * this gradually returns to its original speed
         */
        void slowDown();

        /**
         * @return True if this entity is slowed, false otherwise
         */
        bool isSlowed();

        /**
         * @return True if this entity is sped, false otherwise
         */
        bool isSped();

        /**
         * If the variable "skin" is not yet initialized, a random index will be assigned to it, hence a random skin
         * @return An index for the skin this entity is using
         */
        int getSkin();

        /**
         * @return The movement speed of the entity
         */
        float getMovementSpeed() const;

        /**
         * @return The global bounds of the entity
         */
        std::shared_ptr<GlobalBounds> getGlobalBounds() const;

        /**
         * Sets the center position of the entity to (x, y)
         * @param x: new x coordinate of the entity
         * @param y: new y cooridnate of the entity
         */
        void setPosition(float x, float y);

        /**
         * Moves the entity by adding an offset to its center position
         * @param xOffset: x coordinate offset
         * @param yOffset: y coordinate offset
         */
        virtual void move(const float& xOffset, const float& yOffset);
};
} // namespace TH

#endif // TURBOHIKER_ENTITY_H
