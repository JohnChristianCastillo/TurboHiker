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
        Timer();
        static std::shared_ptr<Timer> timer;
        std::chrono::high_resolution_clock::time_point initialTime;
        std::chrono::duration<float> elapsedTime{};
        float gameTime = 0.f;

public:
        /**
         * Instantiates a Timer instance if it hasn't been instantiated yet and returns this
         * Otherwise just return the already instantiated Timer object
         * @return The unique instance of Timer
         */
        static std::shared_ptr<Timer> getInstance();

        /**
         * Restarts the clock, setting the initial time to the current time
         */
        void restart();

        /**
         * increases the time elapsed time
         */
        void tick();

        /**
         * Resets the game time to 0
         */
        void resetGameTime();

        /**
         * @return The time that elapsed since the initial time
         */
        float getElapsedtime();

        /**
         * @return The game time
         */
        float getGameTime() const;

        /**
         * Increments the game time by incr
         * @param incr: The factor by which we increment the game time
         */
        void incrementGameTime(float incr);
};
} // namespace singleton
} // namespace TH

#endif // TURBOHIKER_TIMER_H
