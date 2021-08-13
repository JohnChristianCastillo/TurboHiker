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


class Controller {
    std::shared_ptr<Model> model;
    std::shared_ptr<View> view;
    std::shared_ptr<LiveScoring> scoringSystem;
    float fps;

public:
    explicit Controller(float fps):fps(fps)
    {
        // Initialize transformation instance
        float screenHeight = float(sf::VideoMode::getDesktopMode().height) * 0.75f;
        float screenWidth = screenHeight/8.f*6.f;
        std::shared_ptr<singleton::Transformation> transformation = singleton::Transformation::init(Dimentions{screenWidth, screenHeight});

        scoringSystem = std::make_shared<LiveScoring>();
        model = std::make_shared<Model>(fps, scoringSystem);
        view = std::make_shared<View>(fps);
    }


    void resetObjects(){
        scoringSystem = std::make_shared<LiveScoring>();
        model = std::make_shared<Model>(fps, scoringSystem);
        view = std::make_shared<View>(fps);
    }

    void run(){
        /// CLOCK
        std::shared_ptr<singleton::Timer> timer = singleton::Timer::getInstance();
        view->startScreen();
        bool stillOnStartScreen{true};
        bool stillOnEndScreen{false};
        //view->draw();
        bool inputBlocked = true;
        bool finishLineGenerated = false;
        std::vector<Input> inputs{};

        while (view->getWindow().isOpen()) {
            // poll for Enter on start screen
            while(stillOnStartScreen){
                if (view->pollEvent() == Input::ZERO) {
                    return;
                }
                inputs = view->getKeyboardInput();
                for (const auto &in : inputs) {
                    if(in == Input::ENTER){
                        timer->restart();
                        timer->resetGameTime();
                        while(timer->getGameTime() <= 3){
                            timer->tick();
                            timer->restart();
                            // we start the countDown
                            view->draw2(model, 3-timer->getGameTime(), false, true);
                            timer->incrementGameTime(timer->getElapsedtime());
                        }
                        timer->restart();
                        timer->resetGameTime();
                        stillOnStartScreen = false;
                    }
                }
            }
            // poll for when on endScreen
            while(stillOnEndScreen){
                if (view->pollEvent() == Input::ZERO) {
                    return;
                }
                for (const auto &in : inputs) {
                    if (view->pollEvent() == Input::ZERO) return;

                    if(in == Input::ENTER){
                        resetObjects();
                        timer->resetGameTime();
                        view->draw2(model, timer->getGameTime());
                        stillOnEndScreen = false;
                        finishLineGenerated = false;
                    }
                }
            }
            timer->tick();
            float elapsedTime = timer->getElapsedtime();
            if(timer->getElapsedtime() >= 1/model->getFps()) {
                timer->restart();

                /// poll event
                if (view->pollEvent() == Input::ZERO) return;
                /// get keyboard input
                inputs = view->getKeyboardInput();
                bool moved = false;
                std::shared_ptr<MainCharacter> mc = model->getMainCharacter();

                // We always move the AI up
                model->setSimpleAIMove(Move(0,
                                            -model->getSimpleAI()->getMovementSpeed()*elapsedTime));
                for (const auto &in : inputs) {
                    switch (in) {
                        case UP:
                            model->setBackgroundMove(Move(0,mc->getMovementSpeed() * elapsedTime));
                            moved = true;
                            break;
                        case DOWN:
                            model->setBackgroundMove(Move(0, -mc->getMovementSpeed() * elapsedTime));
                            moved = true;
                            break;
                        case LEFT:
                            model->setPlayerMove(Move(- mc->getMovementSpeed() * elapsedTime, 0));
                            moved = true;
                            break;
                        case RIGHT:
                            model->setPlayerMove(Move(mc->getMovementSpeed() * elapsedTime, 0)) ;
                            moved = true;
                            break;
                        case HONKING:
                            model->getMainCharacter()->setYelling(true);
                            std::cout << "MC is Yelling at the enemy \n";
                        case SCARING:
                            model->getMainCharacter()->setScareEnemy(true);
                            std::cout << "MC is scaring the enemy \n";
                        default:
                            break;
                    }
                }


                // if the player is moved then we want to first check for collisions
                if (moved) {
                    if(timer->getGameTime() > 30 and !finishLineGenerated){
                        finishLineGenerated = true;
                        model->generateFinishLine();
                    }
                    //model->collision, model->getBackgrounds(), model->getEnemies(), model->getSimpleAI(), model->getScoringSystem(),nControl();
                    model->moveMC();
                    model->moveBackground();
                    model->moveEnemies();
                }
            }
            model->moveSimpleAI();
            model->screenCollisionControl();
            if(model->collisionControl(finishLineGenerated)){

                view->endScreen(model->getScoringSystem());
                stillOnEndScreen = true;
                continue;
            }
            model->resetMoves();
            view->draw2(model, timer->getGameTime(), finishLineGenerated);
            timer->incrementGameTime(elapsedTime);

        }

    }


    //////////////////////////////////////////////////////
    /// This section contains VIEW REQUEST FUNCTIONS ////
    ////////////////////////////////////////////////////

};


#endif//TURBOHIKER_CONTROLLER_H
