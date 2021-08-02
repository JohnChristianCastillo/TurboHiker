//
// Created by JOHN CHRISTIAN CASTILLO on 7/18/2021.
//

#ifndef TURBOHIKER_CONTROLLER_H
#define TURBOHIKER_CONTROLLER_H

#include "../Model/Model.h"
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
        std::chrono::time_point<std::chrono::high_resolution_clock> initialTime =
                std::chrono::high_resolution_clock::now();
        view->draw2(model->getMainCharacter(), model->getBackgrounds(), model->getEnemies());
        //view->draw();
        std::tuple<float, float> viewCoords = singleton::Transformation::getInstance()->modelToView(model->getMainCharacter()->getGlobalBounds());
        std::cout << "MC position:" << std::get<0>(viewCoords) << ", " << std::get<1>(viewCoords) << std::endl;
        while (view->getWindow().isOpen()) {
            std::chrono::time_point<std::chrono::high_resolution_clock> finalTime =
                    std::chrono::high_resolution_clock::now();
            std::chrono::duration<float> elapsedTime = finalTime - initialTime;
            elapsedTime.count();
            initialTime = finalTime;


            /// poll event
            if(view->pollEvent() == Input::ZERO) return;
            /// get keyboard input
            Input in = view->getKeyboardInput();
            bool moved = false;
            std::shared_ptr<MainCharacter> mc = model->getMainCharacter();

            switch (in){

                case UP:
                    model->setBackgroundMoveY(model->getBackgroundMove().y + mc->getMovementSpeed()*elapsedTime.count());
                    moved = true;
                    break;
                case DOWN:
                    model->setBackgroundMoveY(model->getBackgroundMove().y - mc->getMovementSpeed()*elapsedTime.count());
                    moved = true;
                    break;

                case LEFT:
                    model->setPlayerMoveX(model->getPlayerMove().x - mc->getMovementSpeed()*elapsedTime.count());
                    moved = true;
                    break;

                case RIGHT:
                    model->setPlayerMoveX(model->getPlayerMove().x + mc->getMovementSpeed()*elapsedTime.count());
                    moved = true;

                default:
                    break;
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
            if(moved){

                //model->collisionControl();
                model->moveMC();
                model->moveBackground();
                model->moveEnemies();
                model->screenCollisionControl();
                model->collisionControl();
                view->draw2(mc, model->getBackgrounds(), model->getEnemies());
                model->resetMoves();
                //view->draw();

            }


        }

    }


    //////////////////////////////////////////////////////
    /// This section contains VIEW REQUEST FUNCTIONS ////
    ////////////////////////////////////////////////////

};


#endif//TURBOHIKER_CONTROLLER_H
