//
// Created by reed on 31.07.21.
//

#ifndef TURBOHIKER_BACKGROUND_H
#define TURBOHIKER_BACKGROUND_H
#include "Entity.h"

namespace TH {
class Background : public Entity
{
public:
        /**
         * Instantiates a background object at the center off the screen, vertically offset by a value generated by
         * the Entity maker. This is used to produce a treadmill-like effect
         * @param centerOffset: verical center offset of the background
         */
        explicit Background(float centerOffset);

        /**
         * @return The type of this Entity, here "background"
         */
        EntityTypes getType() const override { return EntityTypes::background; }
};
} // namespace TH

#endif // TURBOHIKER_BACKGROUND_H
