//
// Created by JOHN CHRISTIAN CASTILLO on 7/18/2021.
//

#ifndef TURBOHIKER_TURBOHIKER_H
#define TURBOHIKER_TURBOHIKER_H

#include "Controller/Controller.h"
#include "Model/Model.h"
#include "SFML/Graphics.hpp"
#include "UserInterface/UserInterface.h"
class TurboHiker {
    std::shared_ptr<Model> model;
    std::shared_ptr<UserInterface> interface;
    std::shared_ptr<Controller> controller;

    float framerate;

public:
    explicit TurboHiker(float framerate):model{std::make_shared<Model>(Model{})},
                                           controller{std::make_shared<Controller>(framerate, model)},
                                         interface{std::make_shared<UserInterface>(UserInterface{controller})},
                          framerate(framerate)
    {
        float screenHeight = float(sf::VideoMode::getDesktopMode().height) * 0.75f;
        float screenWidth = screenHeight/8*6;
        std::shared_ptr<singleton::Transformation> transformation = singleton::Transformation::init(Dimentions{screenWidth, screenHeight});

        std::cout << singleton::Transformation::getInstance()->getScreenDimentions().width << std::endl;
        std::cout << transformation->getScreenDimentions().width << std::endl;

    }
    void run() {
        //Initialize the game window
        sf::RenderWindow window(sf::VideoMode(static_cast<unsigned int>(singleton::Transformation::getInstance()->getScreenDimentions().width),
                                              static_cast<unsigned int>(singleton::Transformation::getInstance()->getScreenDimentions().height)),
                                "TurboHiker!!!");

        /**
         * Start main loop here
         */
        /// CLOCK
        // sf::Clock clock; //todo: make sure even with diff cpu's, time passes by at the same rate
        std::chrono::time_point<std::chrono::high_resolution_clock> initialTime =
                std::chrono::high_resolution_clock::now();

        while (window.isOpen()) {
            std::chrono::time_point<std::chrono::high_resolution_clock> finalTime =
                    std::chrono::high_resolution_clock::now();
            std::chrono::duration<float> elapsedTime = finalTime - initialTime;
            initialTime = finalTime;

            /// check if player wants to exit game
            sf::Event event{};
            while (window.pollEvent(event)) {
                switch (event.type) {
                    case sf::Event::Closed:
                        window.close();
                        break;
                    case sf::Event::KeyPressed:
                        if (event.key.code == sf::Keyboard::Escape) {
                            window.close();
                        }
                        break;
                }
            }
            interface->gatherMovement();

            interface->display(window);

            window.display();
            /*/// Player and background movement
            std::shared_ptr<sf::Vector2f> playerMove = std::make_shared<sf::Vector2f>(0.f, 0.f);
            controller->gatherPlayerMovement(speed, elapsedTime);
            std::shared_ptr<sf::Vector2f> backgroundMove = std::make_shared<sf::Vector2f>(0.f, 0.f);
            controller->gatherBackgroundMovement(backgroundMove, speed, elapsedTime);
*/
            /// Box collisions
            /*for(auto& wall:walls) {
                   sf::FloatRect playerBounds = carSprite.getGlobalBounds();
                   sf::FloatRect wallBounds = wall.getGlobalBounds();

                   // gives us an outline with as offset our next move
                   nextPos = playerBounds;
                   nextPos.left += (playerMove.x - backgroundMove.x) * 10;
                   nextPos.top += (playerMove.y - backgroundMove.y) * 10;

                   // todo: remove this for final
                   nextBox.setPosition(nextPos.left, nextPos.top);

                   if (wallBounds.intersects(nextPos)) {
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
                               playerBounds.top + playerBounds.height <
                                   wallBounds.top + wallBounds.height &&
                               playerBounds.left < wallBounds.left + wallBounds.width &&
                               playerBounds.left + playerBounds.width > wallBounds.left) {
                                   playerMove.y = 0.f;
                                   // bottom of player set to top of wall
                                   carSprite.setPosition(playerBounds.left,
                                                         wallBounds.top - playerBounds.height);
                           }
                           // Player Top collision
                           else if (playerBounds.top > wallBounds.top &&
                                    playerBounds.top + playerBounds.height >
                                        wallBounds.top + wallBounds.height &&
                                    playerBounds.left < wallBounds.left + wallBounds.width &&
                                    playerBounds.left + playerBounds.width > wallBounds.left) {
                                   playerMove.y = 0.f;
                                   // top of player set to bottom of wall                 plus cause y goes
           down carSprite.setPosition(playerBounds.left, wallBounds.top + wallBounds.height);
                           }

                           // Player right collision
                           else if (playerBounds.left < wallBounds.left &&
                                    playerBounds.left + playerBounds.width <
                                        wallBounds.left + wallBounds.width &&
                                    playerBounds.top < wallBounds.top + wallBounds.height &&
                                    playerBounds.top + playerBounds.height > wallBounds.top) {
                                   playerMove.x = 0.f;
                                   carSprite.setPosition(wallBounds.left - playerBounds.width,
                                                         playerBounds.top);
                           }
                           // Player Left collision
                           else if (playerBounds.left > wallBounds.left &&
                                    playerBounds.left + playerBounds.width >
                                        wallBounds.left + wallBounds.width &&
                                    playerBounds.top < wallBounds.top + wallBounds.height &&
                                    playerBounds.top + playerBounds.height > wallBounds.top) {
                                   playerMove.x = 0.f;
                                   carSprite.setPosition(wallBounds.left + wallBounds.width,
                                                         playerBounds.top);
                           }
                   }
           }*/
            /**
             * model.scroll
             */
            /*if (backgroundImages.at(0)->getPosition().y > screenDimensions->y) {
                    model->generateEnemies();
                    backgroundImages.at(2)->setPosition(backgroundImages.at(0)->getPosition().x,
                                                        backgroundImages.at(0)->getPosition().y);
                    backgroundImages.at(0)->setPosition(
                        backgroundImages.at(0)->getPosition().x,
                        backgroundImages.at(0)->getPosition().y -
                        backgroundImages.at(0)->getGlobalBounds().height * 2);
            } else if (backgroundImages.at(1)->getPosition().y > screenDimensions->y) {
                    model->generateEnemies();
                    backgroundImages.at(2)->setPosition(backgroundImages.at(1)->getPosition().x,
                                                        backgroundImages.at(1)->getPosition().y);
                    backgroundImages.at(1)->setPosition(
                        backgroundImages.at(1)->getPosition().x,
                        backgroundImages.at(1)->getPosition().y -
                        backgroundImages.at(1)->getGlobalBounds().height * 2);
            }

            backgroundImages.at(1)->move(*backgroundMove);
            backgroundImages.at(2)->move(*backgroundMove);
            backgroundImages.at(0)->move(*backgroundMove);
            mainCharacter->move(*playerMove);

            window->draw(*backgroundImages.at(2));
            window->draw(*backgroundImages.at(0));
            window->draw(*backgroundImages.at(1));

            /// Visualizing next box:
            *//*window->draw(nextBox);
                         *//*

                        /// Window collision control
                        /// left collision

                        if (mainCharacter->getPosition().x - mainCharacter->getGlobalBounds().width / 2 < 0) {
                                mainCharacter->setPosition(mainCharacter->getGlobalBounds().width / 2,
                                                           mainCharacter->getPosition().y);
                        }
                        /// right collision
                        if (mainCharacter->getPosition().x + mainCharacter->getGlobalBounds().width >
                            screenDimensions->x) {
                                mainCharacter->setPosition(screenDimensions->x - mainCharacter->getGlobalBounds().width,
                                                           mainCharacter->getPosition().y);
                        }
                        UserInterface.setCenter(position); // center camera on position
                        window->setView(UserInterface);
                        window->draw(*mainCharacter);

                        /// Draw Walls
                        for (std::shared_ptr<sf::RectangleShape>& enemy : enemies) {
                                enemy->move(*backgroundMove);
                                window->draw(*enemy);
                        }

                        window->display();
                        window->clear();*/
        }
    }
};


#endif//TURBOHIKER_TURBOHIKER_H
