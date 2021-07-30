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

    //////////////////////////////////////////////////////
    /// This section contains MODEL REQUEST FUNCTIONS ///
    ////////////////////////////////////////////////////
    /**
     * @return a const copy of the main character
     */
    std::shared_ptr<MainCharacter> getMainCharacter(){
        return model->getMainCharacter();
    }

    std::vector<std::shared_ptr<Enemy>> getEnemies(){
        return model->getEnemies();
    }

    void moveRight(const float elapsedTime){
        //playerMove.x += model->getMainCharacter()->getMovementSpeed()*elapsedTime;
        //std::shared_ptr<Coordinates> newCoords = model->getMainCharacter()->moveRight(elapsedTime*10.f);
        //std::shared_ptr<singleton::Transformation> trans = singleton::Transformation::getInstance();
        //std::tuple<float,float> x = trans->modelToView(newCoords);

    }
    void moveLeft(const float elapsedTime){
        //playerMove.x -= model->getMainCharacter()->getMovementSpeed()*elapsedTime;

        //float move = model->getMainCharacter()->getMovementSpeed()/model->getFps();
        //if(model->getMainCharacter()->getCoordinates()->lowLeft.first + move >= 0){
        //    model->getMainCharacter()->move(-move, 0);
        //}
        //std::cout << "Left" << std::endl;
    }

    /**
     * loop over all the enemy entities and move them
     * at the same time, clear undisplayed enemies from the vector
     */
    void moveEnemies(const float elapsedTime){
        //for(int i = model->getEnemies().size()-1; i >= 0; --i){
        //    model->getEnemies().at(i)->move(0, model->getMainCharacter()->getMovementSpeed()/model->getFps());
        //    if(model->getEnemies().at(i)->getCoordinates()->lowLeft.second > 8.f){
//
        //        model->getEnemies().erase(model->getEnemies().begin()+i);
        //    }
        //}
        //backgroundMove.y += 10*elapsedTime;
    }

    /*
    //Input input = view->run();
    //std::tuple<Input, float> input = view->run();
    view->init();
    std::tuple<Input,float> input;
    do{
        //while(std::get<0>(input) != Input::ZERO){
        //while(input != Input::ZERO){
        bool moved = false;
        view->draw();
        input = view->mainloop();
        /*
        std::shared_ptr<MainCharacter> mc = model->getMainCharacter();
        float elapsedTime = std::get<1>(input);
        Input movement = std::get<0>(input);
        if(movement == Input::UP){
            model->setBackgroundMoveY(model->getBackgroundMove().y + mc->getMovementSpeed()*elapsedTime);
            moved = true;

        }
        else if(movement == Input::LEFT){
            model->setPlayerMoveX(model->getPlayerMove().x - mc->getMovementSpeed()*elapsedTime);
            moved = true;
        }
        else if(movement == Input::RIGHT){
            model->setPlayerMoveX(model->getPlayerMove().x + mc->getMovementSpeed()*elapsedTime);
            moved = true;
        }

        // if the player is moved then we want to first check for collisions
        if(moved){
            //model->checkMoveValidity();
            //model->moveMC();
            view->draw();
        }
    while(std::get<0>(input) != Input::ZERO);
     */

    void run(){
        /// CLOCK
        std::chrono::time_point<std::chrono::high_resolution_clock> initialTime =
                std::chrono::high_resolution_clock::now();
        view->init();
        view->draw();
        while (view->getWindow().isOpen()) {
            std::chrono::time_point<std::chrono::high_resolution_clock> finalTime =
                    std::chrono::high_resolution_clock::now();
            std::chrono::duration<float> elapsedTime = finalTime - initialTime;
            elapsedTime.count();
            initialTime = finalTime;

            /// poll event
            if(view->pollEvent() == Input::ZERO) return;
            /// get keyboard input
            Input in = view->getKeyboardInput(elapsedTime);

            view->draw();

        }

    }

    //////////////////////////////////////////////////////
    /// This section contains VIEW REQUEST FUNCTIONS ////
    ////////////////////////////////////////////////////

};


#endif//TURBOHIKER_CONTROLLER_H
