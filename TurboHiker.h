//
// Created by JOHN CHRISTIAN CASTILLO on 7/18/2021.
//

#ifndef TURBOHIKER_TURBOHIKER_H
#define TURBOHIKER_TURBOHIKER_H

#include "Controller/Controller.h"
#include "Model/Model.h"
#include "SFML/Graphics.hpp"
#include "View/View.h"
class TurboHiker {
    std::shared_ptr<Model> model;
    std::shared_ptr<View> view;
    std::shared_ptr<Controller> controller;

public:
    explicit TurboHiker(float fps):model{std::make_shared<Model>(Model(fps))}
    {



        // Initialize transformation instance
        float screenHeight = float(sf::VideoMode::getDesktopMode().height) * 0.75f;
        float screenWidth = screenHeight/8*6;
        std::shared_ptr<singleton::Transformation> transformation = singleton::Transformation::init(Dimentions{screenWidth, screenHeight});

        // Initialization of view NEEDS TO HAPPEN after initialization of the transformation class
        // this is due to the fact that view makes use of Transformation to initialize the window
        std::cout << singleton::Transformation::getInstance()->getScreenDimentions().width << std::endl;
        std::cout << transformation->getScreenDimentions().width << std::endl;

        view = std::make_shared<View>(fps);
        controller = std::make_shared<Controller>(model, view);


    }
    void run(){
        controller->run();
    }
};


#endif//TURBOHIKER_TURBOHIKER_H
