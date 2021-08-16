//
// Created by JOHN CHRISTIAN CASTILLO on 7/18/2021.
//

#ifndef TURBOHIKER_CONTROLLER_H
#define TURBOHIKER_CONTROLLER_H

#include "../Model/Model.h"
#include "../Singletons/Timer.h"
#include "../Singletons/Transformation.h"
#include "../View/View.h"
#include <iostream>
#include <utility>
#include <vector>

namespace TH {
class Controller
{
        std::shared_ptr<Model> model;
        std::shared_ptr<SFML::View> view;
        std::shared_ptr<OBSERVER::LiveScoring> scoringSystem;
        float fps;                   // framerate of the user
        std::vector<Input> inputs{}; // holds the keyboard input of the user
public:
        /**
         * Constructs the Controller object together with the:
         *      1: Scoring system
         *      2: Model object
         *      3: View object
         * @param fps : Framerate of the user's monotor
         */
        explicit Controller(float fps);

        /**
         * Performs necessary reset of objects that needs to be on a fresh state to start a fresh game
         */
        void resetObjects();

        /**
         * Traps the user in the end screen after finishing the game
         * Being only able to escape if the Enter key is pressed
         * @param stillOnEndScreen: boolean variable telling us if we're still on the end screen
         * @param stillOnStartScreen: boolean variable that we need to change to true if the user wants to play another
         *                            game
         * @param finishLineGenerated: boolean variable that we need to change to false if the user plays another game
         * @param timer: singleton timer object that oversees the game time
         */
        void pollForEndScreen(bool& stillOnEndScreen, bool& stillOnStartScreen, bool& finishLineGenerated,
                              std::shared_ptr<singleton::Timer>& timer);

        /**
         * Traps the user in the start screen after finishing the game
         * Being only able to escape if the Enter key is pressed
         * @param stillOnStartScreen: boolean variable telling us if we are still within the start screen
         * @param timer: singleton timer object that oversees the game time
         */
        void pollForStartScreen(bool& stillOnStartScreen, std::shared_ptr<singleton::Timer>& timer);

        /**
         * Polls for keyboard input
         * @param elapsedTime: float variable telling us how much time has elapsed
         * @return true if a movement has been polled, false otherwise
         */
        bool getKeyboardInput(const float& elapsedTime);

        /**
         * Runs the Turbo Hiker game
         */
        void run();
};
} // namespace TH

#endif // TURBOHIKER_CONTROLLER_H
