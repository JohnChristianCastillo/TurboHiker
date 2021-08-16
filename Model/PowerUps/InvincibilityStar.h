//
// Created by reed on 15.08.21.
//

#ifndef TURBOHIKER_INVINCIBILITYSTAR_H
#define TURBOHIKER_INVINCIBILITYSTAR_H

#include "PowerUp.h"
namespace TH {
class InvincibilityStar : public PowerUp
{

public:
        EntityTypes getType() const override;
        explicit InvincibilityStar(const float& horizontalOffset);
};
} // namespace TH

#endif // TURBOHIKER_INVINCIBILITYSTAR_H
