//
// Created by JOHN CHRISTIAN CASTILLO on 7/18/2021.
//

#ifndef TURBOHIKER_VIEW_H
#define TURBOHIKER_VIEW_H

#include "../Model/Background.h"
#include "../Model/Enemy.h"
#include "../Model/MainCharacter.h"
#include "../Singletons/Transformation.h"
#include "SFML/Graphics.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include <chrono>
#include <iostream>
#include <utility>


class View {


    /// this can be deleted since it's in the singleton class but it's easier to call it this way
    float screenHeight = float(sf::VideoMode::getDesktopMode().height) * 0.75f;
    float screenWidth = screenHeight/8.f*6.f;

    sf::RenderWindow window{sf::VideoMode(static_cast<unsigned int>(screenWidth),
                                                static_cast<unsigned int>(screenHeight)),
                                                     "TurboHiker!!!"};

public:
    const sf::RenderWindow &getWindow() const;

private:
    // Main Character entity:
    sf::Texture car;

    sf::RectangleShape carSprite;

    // Enemy textures;
    std::vector<sf::Texture> enemyTextures;
    // Background Entities:
    sf::Texture backgroundTexture;
    // the idea here is to have a treadmill like background that will give the illusion that the background is continuous
    sf::Sprite backgroundImage1;
    sf::Sprite backgroundImage2;
    sf::Sprite backgroundImage3;

    float speed = 1000.0f;

    // Set up viewport
    sf::View view;
    // make the player the focus point of view
    sf::Vector2f position{singleton::Transformation::getInstance()->getScreenDimentions().width/2,
                          singleton::Transformation::getInstance()->getScreenDimentions().height/ 2.3f};

public:
    /*
    void display(sf::RenderWindow& window) const{
        window.clear(sf::Color::Cyan);
        drawMainCharacter(window);
    }*/

    /**
     * Initialize the window our user will interact with
     * @param fps: Frame limit set by user
     */

    View(const float fps){
        initializeWindow(fps);
        loadTextures();
        assignBGandMCTextures();
        // initialize to cover the whole screen
        view.reset(sf::FloatRect(0, 0, screenWidth, screenHeight));
        // how much of the view we want to see
        view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
    }

    void initializeWindow(const float fps){
        // create an instance of the window
        window.setFramerateLimit(static_cast<unsigned int>(fps));

    }

    void loadTextures(){
        if (!car.loadFromFile("../assets/cars/1.png")) {
            std::cout << "bg img not found" << std::endl;
        }
        if (!backgroundTexture.loadFromFile("../assets/highway.png")) {
            std::cout << "bg img not found" << std::endl;
        }
        sf::Texture tempTure{};
        for(int i=1; i<=12; ++i){
            std::string fileLocation = "../assets/cars/"+std::to_string(i)+".png";
            if (!tempTure.loadFromFile(fileLocation)) {
                std::cout << "bg img not found" << std::endl;
            }
            enemyTextures.push_back(tempTure);
        }

    }
    void assignBGandMCTextures(){
        backgroundImage1.setScale(1.0f, static_cast<float>(screenHeight)/static_cast<float>(backgroundTexture.getSize().y));
        backgroundImage2.setScale(1.0f, static_cast<float>(screenHeight)/static_cast<float>(backgroundTexture.getSize().y));
        backgroundImage3.setScale(1.0f, static_cast<float>(screenHeight)/static_cast<float>(backgroundTexture.getSize().y));
        backgroundImage1.setTexture(backgroundTexture);
        backgroundImage2.setTexture(backgroundTexture);
        backgroundImage3.setTexture(backgroundTexture);

        sf::RectangleShape carObject(sf::Vector2f(30, 60));
        carSprite = std::move(carObject);
        carSprite.setTexture(&car);
        carSprite.setPosition(backgroundImage1.getGlobalBounds().width / 2,
                              backgroundImage1.getGlobalBounds().height - carSprite.getSize().y);

    }
    Input pollEvent() {
        sf::Event event{};
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    return Input::ZERO;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Escape) {
                        window.close();
                        return Input::ZERO;
                    }
            }
        }
    }
    Input getKeyboardInput() {

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            sf::Vector2i p = sf::Mouse::getPosition();
            std:: cout << p.x << ", " << p.y << std::endl;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            return Input::RIGHT;

        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            return Input::LEFT;


        } /*else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                        backgroundMove.y += -speed * elapsedTime.count(); //clock.getElapsedTime().asSeconds();
                }*/
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            return Input::UP;

        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            return Input::DOWN;

        }
        return Input::ONE;
    }

    void draw2(const std::shared_ptr<MainCharacter>& mc, const std::vector<std::shared_ptr<Background>>& backgrounds, const std::vector<std::shared_ptr<Enemy>>& enemies){
        std::shared_ptr<singleton::Transformation> transformation = singleton::Transformation::getInstance();
        std::tuple<float, float> carCoords = transformation->modelToView(mc->getGlobalBounds());
        view.setCenter(position); // center camera on position
        carSprite.setPosition(std::get<0>(carCoords), std::get<1>(carCoords));



        std::tuple<float, float> bg1 = transformation->modelToView(backgrounds[0]->getGlobalBounds());
        std::tuple<float, float> bg2 = transformation->modelToView(backgrounds[1]->getGlobalBounds());
        std::tuple<float, float> bg3 = transformation->modelToView(backgrounds[2]->getGlobalBounds());
        backgroundImage1.setPosition(std::get<0>(bg1), std::get<1>(bg1));
        backgroundImage2.setPosition(std::get<0>(bg2), std::get<1>(bg2));
        backgroundImage3.setPosition(std::get<0>(bg3), std::get<1>(bg3));

        std::tuple<float, float> mcWidth = transformation->viewToModel(carSprite.getGlobalBounds().width, carSprite.getGlobalBounds().height);

        //std::cout << "McWidth" << std::get<0>(mcWidth) << " " << std::get<1>(mcWidth) << std::endl;
        //std::cout << "BG 1: "<< std::get<1>(bg1) << std::endl;
        //std::cout << "BG 2: "<< std::get<1>(bg2) << std::endl;
        //std::cout << "BG 3: "<< std::get<1>(bg3) << "\n\n\n"<<  std::endl;

        window.setView(view);

        window.draw(backgroundImage1);
        window.draw(backgroundImage2);
        window.draw(backgroundImage3);
        window.draw(carSprite);

        for (auto& wall : enemies) {
            std::tuple<float, float> wallCoords = transformation->modelToView(wall->getGlobalBounds());

            sf::RectangleShape wallSprite(sf::Vector2f(30, 60));
            wallSprite.setTexture(&enemyTextures[wall->getSkin()]);
            wallSprite.setPosition(std::get<0>(wallCoords), std::get<1>(wallCoords));
            window.draw(wallSprite);
        }

        window.display();
        window.clear();
    }

    void draw(){
        /// Box collisions
/*
        for (auto& wall : walls) {
            sf::FloatRect playerBounds = carSprite.getGlobalBounds();
            sf::FloatRect wallBounds = wall.getGlobalBounds();

            // gives us an outline with as offset our next move
            nextPosition = playerBounds;
            nextPosition.left += (playerMove.x - backgroundMove.x) ;
            nextPosition.top += (playerMove.y - backgroundMove.y) ;

            // todo: remove this for final
            nextBox.setPosition(nextPosition.left, nextPosition.top);

            if (wallBounds.intersects(nextPosition)) {
                std::cout << "Collision" << std::endl;
                /// possible solution1: set playerMove x and y to 0
                /// possible solution2:  first construct left and right collision,
                ///                     bottom-top is simillar but inverted
                //   player            wall
                //  ________          ________
                // |        |        |        |
                // |        |        |        |
                // |        |        |        |
                // |________|        |________|

                // Player Bottom collision
                if (playerBounds.top < wallBounds.top &&
                playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height &&
                playerBounds.left < wallBounds.left + wallBounds.width &&
                playerBounds.left + playerBounds.width > wallBounds.left) {
                    playerMove.y = 0.f;
                    // bottom of player set to top of wall
                    carSprite.setPosition(playerBounds.left, wallBounds.top - playerBounds.height);
                }
                // Player Top collision
                else if (playerBounds.top > wallBounds.top &&
                playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height &&
                playerBounds.left < wallBounds.left + wallBounds.width &&
                playerBounds.left + playerBounds.width > wallBounds.left) {
                    playerMove.y = 0.f;
                    // top of player set to bottom of wall                 plus cause y goes down
                    carSprite.setPosition(playerBounds.left, wallBounds.top + wallBounds.height);
                }

                // Player right collision
                else if (playerBounds.left < wallBounds.left &&
                playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width &&
                playerBounds.top < wallBounds.top + wallBounds.height &&
                playerBounds.top + playerBounds.height > wallBounds.top) {
                    playerMove.x = 0.f;
                    carSprite.setPosition(wallBounds.left - playerBounds.width, playerBounds.top);
                }
                // Player Left collision
                else if (playerBounds.left > wallBounds.left &&
                playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width &&
                playerBounds.top < wallBounds.top + wallBounds.height &&
                playerBounds.top + playerBounds.height > wallBounds.top) {
                    playerMove.x = 0.f;
                    carSprite.setPosition(wallBounds.left + wallBounds.width, playerBounds.top);
                }
            }
        }
*/




/*
        if (carSprite.getPosition().x - carSprite.getGlobalBounds().width / 2 < 0) {
            carSprite.setPosition(carSprite.getGlobalBounds().width / 2, carSprite.getPosition().y);
        }
        /// right collision

        float fDimx{singleton::Transformation::getInstance()->getScreenDimentions().width};
        if (carSprite.getPosition().x + carSprite.getGlobalBounds().width > fDimx) {
            carSprite.setPosition(fDimx - carSprite.getGlobalBounds().width,
                                  carSprite.getPosition().y);
        }
*/
        /**
         * scroll when player hits center of screen
         */
        /*
                    if(carSprite.getPosition().y + carSprite.getGlobalBounds().height/2 > screenHeight/2){
                            std::cout <<carSprite.getPosition().y + carSprite.getGlobalBounds().height/2 << std::endl;
                            std::cout <<screenHeight/2 << std::endl;
                            position.y = carSprite.getPosition().y + carSprite.getGlobalBounds().height/4;
                    }

                    else{
                            position.y = screenHeight/2;
                    }*/

        view.setCenter(position); // center camera on position
        window.setView(view);
        window.draw(carSprite);

/*
        for (auto& wall : walls) {
            wall.move(backgroundMove);
            window.draw(wall);
        }
*/

        window.display();
        window.clear();
        //playerMove = {0.f, 0.f};
        //backgroundMove = {0.f, 0.f};
    }
    /*
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

    void gatherMovement()
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
    */
};


#endif//TURBOHIKER_VIEW_H
