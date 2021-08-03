//
// Created by JOHN CHRISTIAN CASTILLO on 12/24/2020.
//

#ifndef TURBOHIKER_RANDOM_H
#define TURBOHIKER_RANDOM_H

#include "memory"
#include <random>

namespace singleton{
class Random
{
        static std::shared_ptr<Random> random;

public:
        static std::shared_ptr<Random> getInstance()
        {
                if (!random) {
                        random = std::make_shared<Random>();
                        return random;
                }
                return random;
        }

        /**
         * @param left : The leftmost limit within our range
         * @param right : The rightmost limit within our range
         * @return A random number generated from a uniform distribution
         */
        int intInInterval(const int& left, const int& right) const
        {
                /*std::random_device rd; // obtain a random number from hardware
                std::mt19937 gen(rd()); // seed the generator
                std::uniform_int_distribution<> distr(left, right); // define the range
                //to use floats one can use std::uniform_real_distribution<>*/
                return rand() % (left - right + 1) + left;
        }
        /**
         * @param left : The leftmost limit within our range
         * @param right : The rightmost limit within our range
         * @return A random float generated from a uniform distribution
         */
        float floatInInterval(const float& left, const float& right) const
        {
                std::random_device rd;                               // obtain a random number from hardware
                std::mt19937 gen(rd());                              // seed the generator
                std::uniform_real_distribution<> distr(left, right); // define the range
                return distr(gen);
        }
};
}
#endif // TURBOHIKER_RANDOM_H
