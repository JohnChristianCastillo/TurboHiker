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
        //view->draw();
        bool inputBlocked = true;
        bool finishLineGenerated = false;
        while (view->getWindow().isOpen()) {
            timer->tick();
            if(timer->getElapsedtime() >= 1/model->getFps()) {
                float elapsedTime = timer->getElapsedtime();
                timer->restart();

                /// poll event
                if (view->pollEvent() == Input::ZERO) return;
                /// get keyboard input
                std::vector<Input> inputs = view->getKeyboardInput();
                bool moved = false;
                std::shared_ptr<MainCharacter> mc = model->getMainCharacter();
                if(!inputBlocked){
                    for (const auto &in : inputs) {
                        switch (in) {
                            case UP:
                                model->setBackgroundMoveY(model->getBackgroundMove().y + mc->getMovementSpeed() * elapsedTime);moved = true;break;
                            case DOWN:
                                model->setBackgroundMoveY(model->getBackgroundMove().y - mc->getMovementSpeed() * elapsedTime);
                                moved = true;
                                break;
                            case LEFT:
                                model->setPlayerMoveX(model->getPlayerMove().x - mc->getMovementSpeed() * elapsedTime);
                                moved = true;
                                break;
                            case RIGHT:
                                model->setPlayerMoveX(model->getPlayerMove().x + mc->getMovementSpeed() * elapsedTime);
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
                }
                else if(inputBlocked) {
                    for (const auto &in : inputs) {
                        if(in == Input::ENTER){
                            resetObjects();
                            timer->resetGameTime();
                            view->draw2(model, timer->getGameTime());
                            inputBlocked = false;
                            finishLineGenerated = false;
                        }
                    }
                }


                // if the player is moved then we want to first check for collisions
                if (moved) {
                    timer->incrementGameTime(elapsedTime);
                    if(timer->getGameTime() > 2 and !finishLineGenerated){
                        finishLineGenerated = true;
                        model->generateFinishLine();
                    }
                    //model->collisiomc, model->getBackgrounds(), model->getEnemies(), model->getSimpleAI(), model->getScoringSystem(),nControl();
                    model->moveMC();
                    model->moveBackground();
                    model->moveEnemies();
                    model->screenCollisionControl();
                    if(model->collisionControl(finishLineGenerated)){
                        view->endScreen(model->getScoringSystem());
                        inputBlocked = true;
                        continue;
                    }
                    if(finishLineGenerated){
                        view->draw2(model, timer->getGameTime(), true);
                    }
                    else{
                        view->draw2(model, timer->getGameTime());
                    }
                    model->resetMoves();
                    //view->draw();
                }
            }
        }

    }


    //////////////////////////////////////////////////////
    /// This section contains VIEW REQUEST FUNCTIONS ////
    ////////////////////////////////////////////////////

};


#endif//TURBOHIKER_CONTROLLER_H
