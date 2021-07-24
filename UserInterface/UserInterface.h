//
// Created by JOHN CHRISTIAN CASTILLO on 7/18/2021.
//

#ifndef TURBOHIKER_USERINTERFACE_H
#define TURBOHIKER_USERINTERFACE_H

#include "../Model/MainCharacter.h"
#include "../Singletons/Transformation.h"
#include "SFML/Graphics.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"

#include "../Controller/Controller.h"

#include <chrono>
#include <iostream>
#include <utility>


class UserInterface {
    std::shared_ptr<Controller> controller;

    sf::Texture mainCharTexture{};
    std::array<sf::Texture, 12> enemyTextures{};
    sf::Texture backgroundTexture{};

public:
    explicit UserInterface(std::shared_ptr<Controller> controller): controller(std::move(controller)){};
    void display(sf::RenderWindow& window) const{
        window.clear(sf::Color::Cyan);
        drawMainCharacter(window);
    }
    void drawMainCharacter(sf::RenderWindow& window) const{
        auto pp = controller->getMainCharacter()->getCoordinates();
        std::shared_ptr<Coordinates> viewCoords = singleton::Transformation::getInstance()->modelToView(pp);
        float width = viewCoords->upRight.first - viewCoords->lowLeft.first;
        float height = std::abs(viewCoords->upRight.second - viewCoords->lowLeft.second);

        sf::RectangleShape mainCharacter{sf::Vector2f(width, height)};
        //mainCharacter.setTexture(&mainCharTexture);
        mainCharacter.setFillColor(sf::Color::Black);
        mainCharacter.setPosition(width, height);


        sf::View view;
        //initialize to cover the whole screen
        view.reset(sf::FloatRect(0,0, singleton::Transformation::getInstance()->getScreenDimentions().width/2, 1.5*singleton::Transformation::getInstance()->getScreenDimentions().height));
        //how much of the view we want to see
        view.setViewport(sf::FloatRect(0,0,1.0f, 1.0f));
        sf::Vector2f position(singleton::Transformation::getInstance()->getScreenDimentions().width/2, 1.5*singleton::Transformation::getInstance()->getScreenDimentions().height);
        view.setCenter(position);
        window.setView(view);
        window.draw(mainCharacter);
    }
    void drawEnemies()
    {
       for (auto& enemy : controller->getEnemies()) {
            std::shared_ptr<Coordinates> viewCoords = singleton::Transformation::getInstance()->modelToView(enemy->getCoordinates());

            float width = viewCoords->upRight.first - viewCoords->lowLeft.first;
            float height = std::abs(viewCoords->upRight.second - viewCoords->lowLeft.second);

            std::shared_ptr<sf::RectangleShape> enemySprite = std::make_shared<sf::RectangleShape>(sf::Vector2f(width, height));
            enemySprite->setTexture(&enemyTextures.at(1));
            enemySprite->setPosition(viewCoords->lowLeft.first, viewCoords->lowLeft.second);
        }
    }

    const void gatherMovement()
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            controller->moveRight();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            controller->moveLeft();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            controller->moveEnemies();
        }
    }
    
};


#endif//TURBOHIKER_USERINTERFACE_H
