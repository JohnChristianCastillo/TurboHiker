//
// Created by reed on 05.08.21.
//

#ifndef TURBOHIKER_TIMER_H
#define TURBOHIKER_TIMER_H


#include <chrono>
#include <memory>

namespace singleton {
    class Timer {
        static std::shared_ptr<Timer> timer;
        Timer();
        std::chrono::high_resolution_clock::time_point initialTime;
        std::chrono::duration<float> elapsedtime;
        float timeScale;

        public:
            void restart(){
                initialTime = std::chrono::system_clock::now();

            }
            void tick(){
                auto x = std::chrono::high_resolution_clock::now();

                elapsedtime = std::chrono::system_clock::now() - initialTime;
            }

            static std::shared_ptr<Timer> getInstance() {
                if (!timer) {
                    timer = std::make_shared<Timer>(Timer());
                }
                return timer;
            }
            float getElapsedtime(){
                return elapsedtime.count();
            }
    };
}

#endif//TURBOHIKER_TIMER_H
