//
// Created by reed on 05.08.21.
//

#include "Timer.h"
std::shared_ptr<TH::singleton::Timer> TH::singleton::Timer::timer = nullptr;

TH::singleton::Timer::Timer()
{
        restart();
        elapsedTime = std::chrono::duration<float>(0.0f);
}
std::shared_ptr<TH::singleton::Timer> TH::singleton::Timer::getInstance()
{
        if (!timer) {
                timer = std::move(std::make_shared<Timer>(Timer()));
        }
        return timer;
}
void TH::singleton::Timer::restart() { initialTime = std::chrono::system_clock::now(); }
void TH::singleton::Timer::tick()
{
        auto x = std::chrono::high_resolution_clock::now();

        elapsedTime = std::chrono::system_clock::now() - initialTime;
}
void TH::singleton::Timer::resetGameTime() { gameTime = 0; }
float TH::singleton::Timer::getGameTime() const { return gameTime; }
void TH::singleton::Timer::incrementGameTime(float incr) { gameTime += incr; }
float TH::singleton::Timer::getElapsedtime() { return elapsedTime.count(); }