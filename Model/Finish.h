//
// Created by reed on 11.08.21.
//

#ifndef TURBOHIKER_FINISH_H
#define TURBOHIKER_FINISH_H

#include "Entity.h"

namespace TH {
class Finish : public Entity
{
public:
        /**
         * Instantiates a Finish line object
         */
        explicit Finish();

        /**
         * @return the type of the entity, here "finisLine"
         */
        EntityTypes getType() const override;
};
} // namespace TH

#endif // TURBOHIKER_FINISH_H
