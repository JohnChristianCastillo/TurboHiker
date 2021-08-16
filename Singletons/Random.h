//
// Created by JOHN CHRISTIAN CASTILLO on 12/24/2020.
//

#ifndef TURBOHIKER_RANDOM_H
#define TURBOHIKER_RANDOM_H

#include "memory"
#include <random>

namespace TH {
namespace singleton {
class Random
{
        static std::shared_ptr<Random> random;

public:
        /**
         * Instantiates a Random instance if it hasn't been instantiated yet and returns this
         * Otherwise just return the already instantiated Random object
         * @return The unique instance of Random
         */
        static std::shared_ptr<Random> getInstance();

        /**
         * @param left : The leftmost limit within our range
         * @param right : The rightmost limit within our range
         * @return A random number generated from a uniform distribution
         */
        static int intInInterval(const int& left, const int& right);

        /**
         * @param left : The leftmost limit within our range
         * @param right : The rightmost limit within our range
         * @return A random float generated from a uniform distribution
         */
        static float floatInInterval(const float& left, const float& right);
};
} // namespace singleton
} // namespace TH
#endif // TURBOHIKER_RANDOM_H
