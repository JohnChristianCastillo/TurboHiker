//
// Created by reed on 05.08.21.
//

#include "Timer.h"
std::shared_ptr<TH::singleton::Timer> TH::singleton::Timer::timer = nullptr;

TH::singleton::Timer::Timer()
{
        restart();
        timeScale = 1.0f;
        elapsedtime = std::chrono::duration<float>(0.0f);
}