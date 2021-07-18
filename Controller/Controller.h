//
// Created by JOHN CHRISTIAN CASTILLO on 7/18/2021.
//

#ifndef TURBOHIKER_CONTROLLER_H
#define TURBOHIKER_CONTROLLER_H

#include <iostream>
#include <utility>
#include <vector>
#include "../Model/Model.h"

class Controller {
    std::shared_ptr<Model> model;
    int frameRate;
public:
    Controller(int frameRate, std::shared_ptr<Model> model):frameRate(frameRate), model(std::move(model)){};
    /**
     * @return a const copy of the main character
     */
    std::shared_ptr<MainCharacter> getMainCharacter(){
        return model->getMainCharacter();
    }



    std::vector<std::shared_ptr<Enemy>> getEnemies(){
        return model->getEnemies();
    }

    void moveRight(){
        float move = model->getMainCharacter()->getMovementSpeed()/float(frameRate);
        // check if it can move right
        if (model->getMainCharacter()->getCoordinates()->upRight.first + move <= 6) {
            model->getMainCharacter()->move(move, 0);
        }
        std::cout << "Right" << std::endl;
    }
    void moveLeft(){
        float move = model->getMainCharacter()->getMovementSpeed()/float(frameRate);
        if(model->getMainCharacter()->getCoordinates()->lowLeft.first + move >= 0){
            model->getMainCharacter()->move(-move, 0);
        }
        std::cout << "Left" << std::endl;
    }

    /**
     * loop over all the enemy entities and move them
     * at the same time, clear undisplayed enemies from the vector
     */
    void moveEnemies(){
        for(int i = model->getEnemies().size()-1; i >= 0; --i){
            model->getEnemies().at(i)->move(0, model->getMainCharacter()->getMovementSpeed()/float(frameRate));
            if(model->getEnemies().at(i)->getCoordinates()->lowLeft.second > 8.f){

                model->getEnemies().erase(model->getEnemies().begin()+i);
            }
        }
    }
};


#endif//TURBOHIKER_CONTROLLER_H
