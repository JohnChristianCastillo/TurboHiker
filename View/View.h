//
// Created by JOHN CHRISTIAN CASTILLO on 7/18/2021.
//

#ifndef TURBOHIKER_VIEW_H
#define TURBOHIKER_VIEW_H

#include "../Model/Model.h"
#include "../Observers/LiveScoring.h"
#include "../Singletons/Transformation.h"
#include "SFML/Graphics.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include <chrono>
#include <cmath>
#include <iostream>
#include <sstream>
#include <utility>

namespace TH {
namespace SFML {
class View
{
        /// this can be deleted since it's in the singleton class but it's easier to call it this way
        float screenHeight = float(sf::VideoMode::getDesktopMode().height) * 0.75f;
        float screenWidth = screenHeight / 8.f * 6.f;

        sf::RenderWindow window{
            sf::VideoMode(static_cast<unsigned int>(screenWidth), static_cast<unsigned int>(screenHeight)),
            "TurboHiker!!!"};

        // Main Character entity:
        sf::Texture carTexture;
        sf::RectangleShape carSprite;

        // Enemy textures;
        std::vector<sf::Texture> enemyTextures;
        // Background Entities:
        sf::Texture backgroundTexture;
        // the idea here is to have a treadmill like background that will give the illusion that the background is
        // continuous
        sf::Sprite backgroundImage1;
        sf::Sprite backgroundImage2;
        sf::Sprite backgroundImage3;

        sf::Texture finishLineTexture;
        sf::RectangleShape finishSprite;

        sf::Texture invincibilityStarTexture;
        sf::Texture speedBoostTexture;

        float speed = 1000.0f;

        // Set up viewport
        sf::View view;
        // make the player the focus point of view
        sf::Vector2f position{singleton::Transformation::getInstance()->getScreenDimentions().width / 2,
                              singleton::Transformation::getInstance()->getScreenDimentions().height / 2.3f};

        // scoring system entities
        sf::Text scoreText;
        sf::Font retro;

        // keyboard multiple input entities;
        bool upIsPressed{false};
        bool downIsPressed{false};
        bool leftIsPressed{false};
        bool rightIsPressed{false};
        bool playerIsHonking{false};
        bool playerIsScaring{false};

public:
        const sf::RenderWindow& getWindow() const;

        void initScoringSystem()
        {
                retro.loadFromFile("../assets/fonts/Retro Gaming.ttf");
                scoreText.setCharacterSize(20);
                scoreText.setFont(retro);
                scoreText.setString("0");
                scoreText.setFillColor(sf::Color::Black);
                scoreText.setOrigin(scoreText.getGlobalBounds().width / 2, scoreText.getGlobalBounds().height / 2);
                scoreText.setPosition(screenWidth - 200, 10);
        }
        void drawScore(const std::shared_ptr<OBSERVER::LiveScoring>& scoringSystem, const float& gameTime,
                       const float& scareCooldown)
        {
                scoreText.setString(std::to_string(scoringSystem->getScore()) + "\n" + std::to_string(gameTime) +
                                    "\nScare\nCooldown: " + std::to_string(scareCooldown));
                window.draw(scoreText);
        }

        /**
         * Initialize the window our user will interact with
         * @param fps: Frame limit set by user
         */
        View(const float fps, const std::shared_ptr<TH::Model>& model)
        {

                window.setFramerateLimit(static_cast<unsigned int>(fps));

                // initialize the player
                std::shared_ptr<singleton::Transformation> transformation = singleton::Transformation::getInstance();
                Dimentions playerDim =
                    transformation->modelDimToViewDim(model->getMainCharacter()->getGlobalBounds()->dimentions);

                sf::RectangleShape carObject(sf::Vector2f(playerDim.width, playerDim.height));
                carSprite = std::move(carObject);

                loadTextures();
                assignBGandMCTextures();
                // initialize to cover the whole screen
                view.reset(sf::FloatRect(0, 0, screenWidth, screenHeight));
                // how much of the view we want to see
                view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
                initScoringSystem();
        }

        void loadTextures()
        {
                if (!carTexture.loadFromFile("../assets/cars/1.png")) {
                        std::cout << "bg img not found" << std::endl;
                }
                // if (!backgroundTexture.loadFromFile("../assets/highway.png")) {
                if (!backgroundTexture.loadFromFile("../assets/Roads/road_asphalt01.png")) {
                        std::cout << "bg img not found" << std::endl;
                }

                if (!finishLineTexture.loadFromFile("../assets/finishLine.png")) {
                        std::cout << "finish line image not found" << std::endl;
                }

                if (!invincibilityStarTexture.loadFromFile("../assets/invincibilityStar.png")) {
                        std::cout << "invincibility star image not found" << std::endl;
                }
                if (!speedBoostTexture.loadFromFile("../assets/arrow_yellow.png")) {
                        std::cout << "speedboost image not found" << std::endl;
                }

                sf::Texture tempTure{};
                for (int i = 1; i <= 12; ++i) {
                        std::string fileLocation = "../assets/cars/" + std::to_string(i) + ".png";
                        if (!tempTure.loadFromFile(fileLocation)) {
                                std::cout << "bg img not found" << std::endl;
                        }
                        enemyTextures.push_back(tempTure);
                }
        }

        void assignBGandMCTextures()
        {
                backgroundImage1.setScale(
                    static_cast<float>(screenWidth) / static_cast<float>(backgroundTexture.getSize().x),
                    static_cast<float>(screenHeight) / static_cast<float>(backgroundTexture.getSize().y));
                backgroundImage2.setScale(
                    static_cast<float>(screenWidth) / static_cast<float>(backgroundTexture.getSize().x),
                    static_cast<float>(screenHeight) / static_cast<float>(backgroundTexture.getSize().y));
                backgroundImage3.setScale(
                    static_cast<float>(screenWidth) / static_cast<float>(backgroundTexture.getSize().x),
                    static_cast<float>(screenHeight) / static_cast<float>(backgroundTexture.getSize().y));
                backgroundImage1.setTexture(backgroundTexture);
                backgroundImage2.setTexture(backgroundTexture);
                backgroundImage3.setTexture(backgroundTexture);

                carSprite.setTexture(&carTexture);

                sf::RectangleShape finishObject(sf::Vector2f(screenWidth, 60));
                finishSprite = std::move(finishObject);
                finishSprite.setTexture(&finishLineTexture);
                finishSprite.setScale(
                    static_cast<float>(screenWidth) * 2 / static_cast<float>(finishLineTexture.getSize().x),
                    static_cast<float>(screenHeight) / (15 * static_cast<float>(finishLineTexture.getSize().y)));
        }
        Input pollEvent()
        {
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
                        case sf::Event::KeyReleased: {
                                if (event.key.code == sf::Keyboard::Up) {
                                        upIsPressed = false;
                                } else if (event.key.code == sf::Keyboard::Down) {
                                        downIsPressed = false;
                                } else if (event.key.code == sf::Keyboard::Left) {
                                        leftIsPressed = false;
                                } else if (event.key.code == sf::Keyboard::Right) {
                                        rightIsPressed = false;
                                }
                        }
                        }
                }
        }

        std::vector<Input> getKeyboardInput()
        {
                /*if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            sf::Vector2i p = sf::Mouse::getPosition();
            std:: cout << p.x << ", " << p.y << std::endl;
        }*/

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
                        return {Input::ENTER};
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                        leftIsPressed = false;
                        rightIsPressed = true;
                        // retVect.push_back(Input::RIGHT);

                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                        rightIsPressed = false;
                        leftIsPressed = true;

                } /*else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                        backgroundMove.y += -speed * elapsedTime.count(); //clock.getElapsedTime().asSeconds();
                }*/
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                        downIsPressed = false;
                        upIsPressed = true;
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                        upIsPressed = false;
                        downIsPressed = true;
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                        playerIsScaring = true;
                        playerIsHonking = false;
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                        playerIsScaring = false;
                        playerIsHonking = true;
                }

                return produceKeyboardOutput();
        }

        std::vector<Input> produceKeyboardOutput()
        {
                std::vector<Input> retVect{};
                if (upIsPressed) {
                        retVect.push_back(Input::UP);
                } else if (downIsPressed) {
                        retVect.push_back(Input::DOWN);
                }
                if (leftIsPressed) {
                        retVect.push_back(Input::LEFT);
                } else if (rightIsPressed) {
                        retVect.push_back(Input::RIGHT);
                }
                if (playerIsHonking) {
                        retVect.push_back(Input::HONKING);
                        playerIsHonking = false;
                } else if (playerIsScaring) {
                        retVect.push_back(Input::SCARING);
                        playerIsScaring = false;
                }
                return retVect;
        }
        void endScreen(const std::shared_ptr<OBSERVER::LiveScoring>& pointingSystem)
        {
                float score = pointingSystem->getScore();
                float highScore = pointingSystem->getHighScore();
                sf::Text endText;
                endText.setCharacterSize(20);
                endText.setFont(retro);
                endText.setString("HIGH SCORE: " + std::to_string(highScore) +
                                  "\nYOUR SCORE: " + std::to_string(score));
                endText.setFillColor(sf::Color::White);
                endText.setPosition(screenWidth / 2, screenHeight / 2);
                // endText.setOrigin(scoreText.getGlobalBounds().width/2, scoreText.getGlobalBounds().height/2);

                endText.setOrigin(endText.getLocalBounds().left + endText.getLocalBounds().width / 2.0f,
                                  endText.getLocalBounds().top + endText.getLocalBounds().height / 2.0f);

                window.draw(endText);
                window.display();
                window.clear();
        }
        void countDown(bool startCountdown, float time)
        {
                if (startCountdown) {
                        sf::Text countDownText;
                        countDownText.setCharacterSize(20);
                        countDownText.setFont(retro);
                        countDownText.setString("STARTING IN: " + std::to_string(static_cast<int>(std::ceil(time))));
                        countDownText.setFillColor(sf::Color::Black);
                        countDownText.setPosition(screenWidth / 2, screenHeight / 2);
                        // endText.setOrigin(scoreText.getGlobalBounds().width/2, scoreText.getGlobalBounds().height/2);

                        countDownText.setOrigin(
                            countDownText.getLocalBounds().left + countDownText.getLocalBounds().width / 2.0f,
                            countDownText.getLocalBounds().top + countDownText.getLocalBounds().height / 2.0f);

                        window.draw(countDownText);
                }
        }
        void startScreen()
        {
                sf::Text startText;
                startText.setCharacterSize(20);
                startText.setFont(retro);
                startText.setString("PRESS ENTER KEY TO START");
                startText.setFillColor(sf::Color::White);
                startText.setOrigin(startText.getLocalBounds().left + startText.getLocalBounds().width / 2.0f,
                                    startText.getLocalBounds().top + startText.getLocalBounds().height / 2.0f);
                startText.setPosition(screenWidth / 2, screenHeight / 2);

                window.draw(startText);
                window.display();
                window.clear();
        }

        void drawLookAhead(const bool& lookAhead, const std::shared_ptr<TH::Model>& model,
                           const std::shared_ptr<singleton::Transformation>& transformation)
        {
                if (lookAhead) {
                        for (const auto& i : model->getSimpleAI()->getLookAhead()) {
                                std::tuple<float, float> auraPos = transformation->modelToView(i);
                                /// Collision object
                                /// Next box visualization todo: remove for final
                                sf::RectangleShape nextBox{sf::Vector2f(carSprite.getSize())};
                                nextBox.setFillColor(sf::Color::Transparent);
                                nextBox.setOutlineColor(sf::Color::White);
                                nextBox.setOutlineThickness(3.f);
                                nextBox.setPosition(std::get<0>(auraPos), std::get<1>(auraPos));
                                window.draw(nextBox);
                        }
                }
        }

        void drawEnemies(const std::shared_ptr<TH::Model>& model,
                         const std::shared_ptr<singleton::Transformation>& transformation)
        {
                for (auto& wall : model->getEnemies()) {
                        std::tuple<float, float> wallCoords = transformation->modelToView(wall->getGlobalBounds());
                        sf::RectangleShape wallSprite(sf::Vector2f(30, 60));
                        wallSprite.setTexture(&enemyTextures[wall->getSkin()]);
                        wallSprite.setPosition(std::get<0>(wallCoords), std::get<1>(wallCoords));
                        window.draw(wallSprite);
                }
        }

        void drawPowerUps(const std::shared_ptr<TH::Model>& model,
                          const std::shared_ptr<singleton::Transformation>& transformation)
        {
                for (auto& powerUp : model->getPowerUps()) {
                        std::tuple<float, float> wallCoords = transformation->modelToView(powerUp->getGlobalBounds());

                        sf::RectangleShape wallSprite(sf::Vector2f(30, 60));
                        if (powerUp->getType() == EntityTypes::speedUp) {
                                wallSprite.setTexture(&speedBoostTexture);
                        } else if (powerUp->getType() == EntityTypes::invincibilityStar) {
                                wallSprite.setTexture(&invincibilityStarTexture);
                        }
                        wallSprite.setPosition(std::get<0>(wallCoords), std::get<1>(wallCoords));
                        window.draw(wallSprite);
                }
        }

        void drawFinishLine(bool finishLineGenerated, const std::shared_ptr<TH::Model>& model,
                            const std::shared_ptr<singleton::Transformation>& transformation)
        {
                if (finishLineGenerated) {
                        std::tuple<float, float> finishLineCoords =
                            transformation->modelToView(model->getFinishLine()->getGlobalBounds());
                        finishSprite.setPosition(std::get<0>(finishLineCoords), std::get<1>(finishLineCoords));
                        window.draw(finishSprite);
                }
        }

        void drawInvincibilityPrompt(const std::shared_ptr<TH::Model>& model)
        {
                if (model->getMainCharacter()->isInvincible()) {
                        sf::Text startText;
                        startText.setCharacterSize(20);
                        startText.setFont(retro);
                        startText.setString(
                            "INVINCIBLE!! " +
                            std::to_string(static_cast<int>(model->getMainCharacter()->getInvincibilityDuration())));
                        startText.setFillColor(sf::Color::Yellow);
                        startText.setOrigin(startText.getLocalBounds().left + startText.getLocalBounds().width / 2.0f,
                                            startText.getLocalBounds().top + startText.getLocalBounds().height / 2.0f);
                        startText.setPosition(screenWidth / 2, screenHeight / 2);

                        window.draw(startText);
                }
        }

        void drawMC(const std::shared_ptr<TH::Model>& model,
                    const std::shared_ptr<singleton::Transformation>& transformation)
        {
                std::tuple<float, float> carCoords =
                    transformation->modelToView(model->getMainCharacter()->getGlobalBounds());
                view.setCenter(position); // center camera on position
                carSprite.setPosition(std::get<0>(carCoords), std::get<1>(carCoords));
                window.draw(carSprite);
        }
        void drawAI(const std::shared_ptr<TH::Model>& model,
                    const std::shared_ptr<singleton::Transformation>& transformation)
        {
                sf::RectangleShape simpleAISprite(sf::Vector2f(30, 60));
                simpleAISprite.setTexture(&enemyTextures[model->getSimpleAI()->getSkin()]);
                std::tuple<float, float> simpleAiCoords =
                    transformation->modelToView(model->getSimpleAI()->getGlobalBounds());
                simpleAISprite.setPosition(std::get<0>(simpleAiCoords), std::get<1>(simpleAiCoords));
                window.draw(simpleAISprite);
        }
        void drawBackgrounds(const std::shared_ptr<TH::Model>& model,
                             const std::shared_ptr<singleton::Transformation>& transformation)
        {
                std::tuple<float, float> bg1 =
                    transformation->modelToView(model->getBackgrounds()[0]->getGlobalBounds());
                std::tuple<float, float> bg2 =
                    transformation->modelToView(model->getBackgrounds()[1]->getGlobalBounds());
                std::tuple<float, float> bg3 =
                    transformation->modelToView(model->getBackgrounds()[2]->getGlobalBounds());
                backgroundImage1.setPosition(std::get<0>(bg1), std::get<1>(bg1));
                backgroundImage2.setPosition(std::get<0>(bg2), std::get<1>(bg2));
                backgroundImage3.setPosition(std::get<0>(bg3), std::get<1>(bg3));
                window.draw(backgroundImage1);
                window.draw(backgroundImage2);
                window.draw(backgroundImage3);
        }

        void draw(const std::shared_ptr<TH::Model>& model, float gameTime, bool finishLineGenerated = false,
                  bool startCountdown = false, bool lookAhead = false)
        {
                std::shared_ptr<singleton::Transformation> transformation = singleton::Transformation::getInstance();
                window.setView(view);

                drawBackgrounds(model, transformation);
                drawMC(model, transformation);
                drawAI(model, transformation);

                drawLookAhead(lookAhead, model, transformation);

                drawEnemies(model, transformation);

                drawPowerUps(model, transformation);

                drawFinishLine(finishLineGenerated, model, transformation);

                drawScore(model->getScoringSystem(), gameTime, model->getMainCharacter()->getScareCooldown());

                drawInvincibilityPrompt(model);

                countDown(startCountdown, gameTime);

                window.display();
                window.clear();
        }
};
} // namespace SFML
} // namespace TH

#endif // TURBOHIKER_VIEW_H
