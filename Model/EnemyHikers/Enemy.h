//
// Created by JOHN CHRISTIAN CASTILLO on 7/18/2021.
//

#ifndef TURBOHIKER_ENEMY_H
#define TURBOHIKER_ENEMY_H

#include "../Entity.h"

namespace TH {
class Enemy : public Entity
{
protected:
        int yellPoints{}; // counts how many times it has been yelled at
        bool steerRandomly{false};

public:
        /**
         * @return True if Enemy needs to steer randomly, false otherwise
         */
        bool isSteerRandolmy() const;

        /**
         * sets the variable steerRandomly to _steerRandomly
         * @param _steerRandomly
         */
        void setSteerRandolmy(bool _steerRandomly);

        /**
         * @return True if the Enemy has exceeded it's scareThreshold. Meaning it has been frightened enough to be
         *         thrown off the stage. False otherwise
         */
        bool exceededScareThreshold();
};
} // namespace TH

#endif // TURBOHIKER_ENEMY_H
