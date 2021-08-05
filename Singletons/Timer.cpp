//
// Created by reed on 05.08.21.
//

#include "Timer.h"
std::shared_ptr<singleton::Timer> singleton::Timer::timer = nullptr;

singleton::Timer::Timer(){
    restart();
    timeScale = 1.0f;
    elapsedtime = std::chrono::duration<float>(0.0f);
}