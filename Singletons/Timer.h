//
// Created by reed on 05.08.21.
//

#ifndef TURBOHIKER_TIMER_H
#define TURBOHIKER_TIMER_H


#include <chrono>
#include <memory>

namespace TH {
namespace singleton {
class Timer
{
        static std::shared_ptr<Timer> timer;
        Timer();
        std::chrono::high_resolution_clock::time_point initialTime;
        std::chrono::duration<float> elapsedtime;
        float timeScale;
        float gameTime = 0.f;

public:
        void restart() { initialTime = std::chrono::system_clock::now(); }
        void tick()
        {
                auto x = std::chrono::high_resolution_clock::now();

                elapsedtime = std::chrono::system_clock::now() - initialTime;
        }

        static std::shared_ptr<Timer> getInstance()
        {
                if (!timer) {
                        timer = std::move(std::make_shared<Timer>(Timer()));
                }
                return timer;
        }
        void resetGameTime() { gameTime = 0; }
        float getElapsedtime() { return elapsedtime.count(); }

        float getGameTime() { return gameTime; }
        void incrementGameTime(float incr) { gameTime += incr; }
};
} // namespace singleton
} // namespace TH

#endif // TURBOHIKER_TIMER_H
