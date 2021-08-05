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


public:
    Controller(std::shared_ptr<Model> model, std::shared_ptr<View> view):
        model(std::move(model)), view(std::move(view)){};


    void run(){
        /// CLOCK
        std::shared_ptr<singleton::Timer> timer = singleton::Timer::getInstance();
        view->draw2(model->getMainCharacter(), model->getBackgrounds(), model->getEnemies(), model->getSimpleAI(), model->getScoringSystem(), 0.f);
        //view->draw();
        std::tuple<float, float> viewCoords = singleton::Transformation::getInstance()->modelToView(model->getMainCharacter()->getGlobalBounds());
        std::cout << "MC position:" << std::get<0>(viewCoords) << ", " << std::get<1>(viewCoords) << std::endl;
        float gameTime = 0.f;
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

                for (const auto &in : inputs) {
                    switch (in) {
                        case UP:
                            model->setBackgroundMoveY(model->getBackgroundMove().y + mc->getMovementSpeed() * elapsedTime);
                            moved = true;
                            break;
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


                /*
            if(in == Input::UP){
                model->setBackgroundMoveY(model->getBackgroundMove().y + mc->getMovementSpeed()*elapsedTime.count());
                moved = true;
            }
            else if(in == Input::DOWN){
                model->setBackgroundMoveY(model->getBackgroundMove().y - mc->getMovementSpeed()*elapsedTime.count());
                moved = true;
            }
            else if(in == Input::LEFT){
                model->setPlayerMoveX(model->getPlayerMove().x - mc->getMovementSpeed()*elapsedTime.count());
                moved = true;
            }
            else if(in == Input::RIGHT){
                model->setPlayerMoveX(model->getPlayerMove().x + mc->getMovementSpeed()*elapsedTime.count());
                moved = true;
            }*/
                // if the player is moved then we want to first check for collisions
                if (moved) {
                    gameTime += elapsedTime;
                    //model->collisionControl();
                    model->moveMC();
                    model->moveBackground();
                    model->moveEnemies();
                    model->screenCollisionControl();
                    model->collisionControl();
                    view->draw2(mc, model->getBackgrounds(), model->getEnemies(), model->getSimpleAI(), model->getScoringSystem(), gameTime);
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
