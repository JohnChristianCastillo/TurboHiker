//
// Created by JOHN CHRISTIAN CASTILLO on 12/24/2020.
//

#include "Random.h"
std::shared_ptr<TH::singleton::Random> TH::singleton::Random::random = nullptr;
std::shared_ptr<TH::singleton::Random> TH::singleton::Random::getInstance()
{
        if (!random) {
                random = std::make_shared<Random>();
                return random;
        }
        return random;
}
int TH::singleton::Random::intInInterval(const int& left, const int& right)
{
        return rand() % (right - left + 1) + left;
}
float TH::singleton::Random::floatInInterval(const float& left, const float& right)
{
        std::random_device rd;                               // obtain a random number from hardware
        std::mt19937 gen(rd());                              // seed the generator
        std::uniform_real_distribution<> distr(left, right); // define the range
        return static_cast<float>(distr(gen));
}