//
// Created by JOHN CHRISTIAN CASTILLO on 7/18/2021.
//

#ifndef TURBOHIKER_VIEW_H
#define TURBOHIKER_VIEW_H

#include "SFML/Graphics.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "../Singletons/Transformation.h"
#include <chrono>
#include <iostream>
#include <utility>


class View {


    float screenHeight = float(sf::VideoMode::getDesktopMode().height) * 0.75f;
    float screenWidth = screenHeight/8*6;
    sf::RenderWindow window{sf::VideoMode(static_cast<unsigned int>(screenWidth),
                                                static_cast<unsigned int>(screenHeight)),
                                                     "TurboHiker!!!"};

    sf::Texture mainCharTexture{};
    std::array<sf::Texture, 12> enemyTextures{};

public:
    const sf::RenderWindow &getWindow() const;

private:
    // Main Character entity:
    sf::Texture car;

    sf::RectangleShape carSprite;

    // Background Entities:
    sf::Texture backgroundTexture;
    // the idea here is to have a treadmill like background that will give the illusion that the background is continuous
    sf::Sprite backgroundImage1;
    sf::Sprite backgroundImage2;
    sf::Sprite backgroundImage3;

    // The coordinates of the next position our player will move to
    sf::FloatRect nextPosition;
    // The corresponding visualization of the nextPosition
    sf::RectangleShape nextBox;

    std::vector<sf::RectangleShape> walls;

    float speed = 1000.0f;

    // Set up viewport
    sf::View view;
    // make the player the focus point of view
    sf::Vector2f position{singleton::Transformation::getInstance()->getScreenDimentions().width/2,
                          singleton::Transformation::getInstance()->getScreenDimentions().height/ 2.3f};


    /// TODO: DELETE THESE AFTERWARDS
    /// Player and background movement
    sf::Vector2f playerMove{0.f, 0.f};
    sf::Vector2f backgroundMove{0.f, 0.f};
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
    }

    void initializeWindow(const float fps){
        // create an instance of the window
        window.setFramerateLimit(static_cast<unsigned int>(fps));

    }

    void initializeMC(){
        // place main character at the beginning
        /// TODO: Make assets more pliable
        sf::Texture car;
        if (!car.loadFromFile("../assets/cars/4.png")) {
            std::cout << "bg img not found" << std::endl;
        }
        sf::RectangleShape carObject(sf::Vector2f(30, 60));
        carSprite = std::move(carObject);
        carSprite.setTexture(&car);
        carSprite.setPosition(backgroundImage1.getGlobalBounds().width / 2,
                              backgroundImage1.getGlobalBounds().height - carSprite.getSize().y);


        /// Next box visualization todo: remove for final
        sf::RectangleShape nBox{sf::Vector2f(carSprite.getSize())};
        nextBox = std::move(nBox);
        nextBox.setFillColor(sf::Color::Transparent);
        nextBox.setOutlineColor(sf::Color::White);
        nextBox.setOutlineThickness(3.f);

        /**
         * screen scrolling
         */

        unsigned int screenDimx{static_cast<unsigned int>(singleton::Transformation::getInstance()->getScreenDimentions().width)};
        unsigned int screenDimy{static_cast<unsigned int>(singleton::Transformation::getInstance()->getScreenDimentions().height)};

        // initialize to cover the whole screen
        view.reset(sf::FloatRect(0, 0, screenDimx, screenDimy));
        // how much of the view we want to see
        view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
    }
    void init(){
        /// NOTICE: Loading textures has to happen within this function and cannot be delegated due to SFML limitations
        /// SEE: https://www.sfml-dev.org/tutorials/2.1/graphics-sprite.php#the-white-square-problem
        /// TODO: Make assets more pliable
        // assign a background texture
        if (!backgroundTexture.loadFromFile("../assets/highway.png")) {
            std::cout << "bg img not found" << std::endl;
        }

        // repeat background image until window is filled
        //backgroundTexture.setRepeated(true);

        backgroundImage1.setTexture(backgroundTexture);
        backgroundImage2.setTexture(backgroundTexture);
        backgroundImage3.setTexture(backgroundTexture);

        backgroundImage1.setPosition(0, 2.f * backgroundTexture.getSize().y);
        backgroundImage2.setPosition(0, backgroundTexture.getSize().y);
        sf::Texture::bind(&backgroundTexture);

        // place main character at the beginning
        /// TODO: Make assets more pliable
        //sf::Texture car;
        if (!car.loadFromFile("../assets/cars/4.png")) {
            std::cout << "bg img not found" << std::endl;
        }
        sf::RectangleShape carObject(sf::Vector2f(30, 60));
        carSprite = std::move(carObject);
        carSprite.setTexture(&car);
        carSprite.setPosition(backgroundImage1.getGlobalBounds().width / 2,
                              backgroundImage1.getGlobalBounds().height - carSprite.getSize().y);

        /// todo:  WALL
        //std::vector<sf::RectangleShape> walls;

        sf::RectangleShape wall;
        wall.setFillColor(sf::Color::Cyan);
        wall.setSize(sf::Vector2f(3 * carSprite.getGlobalBounds().width, 3 * carSprite.getGlobalBounds().height));
        wall.setPosition(carSprite.getPosition().x + carSprite.getGlobalBounds().width * 3,
                         carSprite.getPosition().y + carSprite.getGlobalBounds().height / 4);

        walls.push_back(wall);
        wall.setPosition(carSprite.getPosition().x - carSprite.getGlobalBounds().width * 3,
                         carSprite.getPosition().y - 2*carSprite.getGlobalBounds().height / 2);
        walls.push_back(wall);


        /// Next box visualization todo: remove for final
        sf::RectangleShape nBox{sf::Vector2f(carSprite.getSize())};
        nextBox = std::move(nBox);
        nextBox.setFillColor(sf::Color::Transparent);
        nextBox.setOutlineColor(sf::Color::White);
        nextBox.setOutlineThickness(3.f);

        /**
         * screen scrolling
         */

        float screenDimx{singleton::Transformation::getInstance()->getScreenDimentions().width};
        float screenDimy{singleton::Transformation::getInstance()->getScreenDimentions().height};

        // initialize to cover the whole screen
        view.reset(sf::FloatRect(0, 0, screenDimx, screenDimy));
        // how much of the view we want to see
        view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
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
    Input getKeyboardInput(std::chrono::duration<float> elapsedTime) {
        /// Player and background movement
        //sf::Vector2f playerMove{0.f, 0.f};
        //sf::Vector2f backgroundMove{0.f, 0.f};
        playerMove = {0.f, 0.f};
        backgroundMove = {0.f, 0.f};
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            std::cout << "Going Right" << std::endl;
            playerMove.x += speed * elapsedTime.count(); // clock.getElapsedTime().asSeconds();
            //controller->moveRight(elapsedTime.count());
            return Input::RIGHT;

        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            std::cout << "Going Left" << std::endl;
            playerMove.x += -speed * elapsedTime.count(); // clock.getElapsedTime().asSeconds();
            //controller->moveLeft(elapsedTime.count());
            return Input::LEFT;


        } /*else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                        backgroundMove.y += -speed * elapsedTime.count(); //clock.getElapsedTime().asSeconds();
                }*/
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            backgroundMove.y += speed * elapsedTime.count(); // clock.getElapsedTime().asSeconds();
            return Input::UP;

        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            backgroundMove.y -= speed * elapsedTime.count(); // clock.getElapsedTime().asSeconds();
            return Input::DOWN;

        }
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

        if (backgroundImage1.getPosition().y > carSprite.getPosition().y) {
            backgroundImage3.setPosition(backgroundImage1.getPosition().x,
                                         backgroundImage1.getPosition().y);
            backgroundImage1.setPosition(backgroundImage1.getPosition().x,
                                         backgroundImage1.getPosition().y -
                                         backgroundImage1.getGlobalBounds().height * 2);
        } else if (backgroundImage2.getPosition().y > carSprite.getPosition().y) {
            backgroundImage3.setPosition(backgroundImage2.getPosition().x,
                                         backgroundImage2.getPosition().y);
            backgroundImage2.setPosition(backgroundImage2.getPosition().x,
                                         backgroundImage2.getPosition().y -
                                         backgroundImage2.getGlobalBounds().height * 2);
        }


        backgroundImage1.move(backgroundMove);
        backgroundImage2.move(backgroundMove);
        backgroundImage3.move(backgroundMove);
        carSprite.move(playerMove);
        window.draw(backgroundImage3);
        window.draw(backgroundImage1);
        window.draw(backgroundImage2);

        /// Window collision control
        /// left collision
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
