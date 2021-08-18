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
        sf::RectangleShape carSprite;

        // Enemy textures;
        std::vector<sf::Texture> enemyTextures;

        // Background Entities:
        std::vector<sf::Texture> backgroundTextures;
        // the idea here is to have a treadmill like background that will give the illusion that the background is
        // continuous
        sf::Sprite backgroundImage1;
        sf::Sprite backgroundImage2;
        sf::Sprite backgroundImage3;

        sf::Texture finishLineTexture;
        sf::RectangleShape finishSprite;

        sf::Texture invincibilityStarTexture;
        sf::Texture speedBoostTexture;
        sf::Texture summonEnemyTexture;
        sf::Texture laserBeamTexture;
        sf::Texture nukeTexture;

        // Set up viewport
        sf::View view;
        // make the player the focus point of view
        sf::Vector2f position{singleton::Transformation::getInstance()->getScreenDimensions().width / 2,
                              singleton::Transformation::getInstance()->getScreenDimensions().height / 2.3f};

        // scoring system entities
        sf::Text scoreText;
        sf::Font retro;

        sf::RectangleShape demoCar{};
        sf::Sprite demoBG{};

        // keyboard multiple input entities;
        bool upIsPressed{false};
        bool downIsPressed{false};
        bool leftIsPressed{false};
        bool rightIsPressed{false};
        bool playerIsHonking{false};
        bool playerIsScaring{false};
        bool wantsToSpawnEnemy{false};

public:
        /**
         * @return the instance of Window
         */
        const sf::RenderWindow& getWindow() const;

        /**
         * Initializes the scoring system
         */
        void initScoringSystem();

        /**
         * Draws the score based off of the scoring system
         * @param scoringSystem: The instance of the LiveScoring observer
         * @param gameTime: The current game time
         * @param scareCoolDown: The cool down left of scareCoolDown
         * @param canSpawnEnemy: boolean value telling us if the main character can spawn an enemy
         */
        void drawScore(const std::shared_ptr<OBSERVER::LiveScoring>& scoringSystem, const float& gameTime,
                       const float& scareCoolDown, const bool& canSpawnEnemy);

        /**
         * Initialize the window our user will interact with
         * @param fps: Frame limit set by user
         */
        View(float fps, const std::shared_ptr<TH::Model>& model);

        /**
         * Loads the correct textures that will be used by the game instance
         */
        void loadTextures();

        /**
         * Assigns the loaded textures to the correct sprite
         * @param bgIndex: index of the background skin that the background going to use
         * @param mcIndex: index of the vehicle skin that the mc is going to use
         */
        void assignBGandMCTextures(const int& bgIndex, const int& mcIndex);

        /**
         * Polls for an event that our system handles
         * @return an object of type Input
         */
        Input pollEvent();

        /**
         * Polls for a keyboard input
         * @return a vector of Input objects
         */
        std::vector<Input> getKeyboardInput();

        /**
         * Produces te correct vector of input objects for the function "getKeyboardInput()"
         * @return a vector of input objects
         */
        std::vector<Input> produceKeyboardOutput();

        /**
         * Displays the end screen after finishing the game
         * @param pointingSystem: The instance of the LiveScoring observer
         */
        void endScreen(const std::shared_ptr<OBSERVER::LiveScoring>& pointingSystem);

        /**
         * Starts the count down of the start of the race
         * @param startCountDown: boolean value indicating if the count down should be started
         * @param time: the game time
         */
        void countDown(bool startCountDown, float time);

        /**
         * Displays the starting screen of the game
         */
        void startScreen();
        /**
         * Draws the lookAhead of the AI
         * @param lookAhead: boolean value indicating if the lookahead should be drawn or not
         * @param model: The instance of Model
         * @param transformation: The instance of Transformation
         */
        void drawLookAhead(const bool& lookAhead, const std::shared_ptr<TH::Model>& model,
                           const std::shared_ptr<singleton::Transformation>& transformation);

        /**
         * Draws the enemies
         * @param model: The instance of Model
         * @param transformation: The instance of Transformation
         */
        void drawEnemies(const std::shared_ptr<TH::Model>& model,
                         const std::shared_ptr<singleton::Transformation>& transformation);

        /**
         * Draws the power ups
         * @param model: The instance of Model
         * @param transformation: The instance of Transformation
         */
        void drawPowerUps(const std::shared_ptr<TH::Model>& model,
                          const std::shared_ptr<singleton::Transformation>& transformation);

        /**
         * Draws the finish line
         * @param finishLineGenerated: boolean value indicating if the finish line is generated
         * @param model: The instance of Model
         * @param transformation: The instance of Transformation
         */
        void drawFinishLine(bool finishLineGenerated, const std::shared_ptr<TH::Model>& model,
                            const std::shared_ptr<singleton::Transformation>& transformation);

        /**
         * Draws the invincibility prompt
         * @param model: The instance of Model
         */
        void drawInvincibilityPrompt(const std::shared_ptr<TH::Model>& model);

        /**
         * Draws the laser beam prompt together with the laser beam
         * @param model: The instance of Model
         * @param transformation: The instance of Transformation
         */
        void drawLaserBeamAndPrompt(const std::shared_ptr<TH::Model>& model,
                                    const std::shared_ptr<singleton::Transformation>& transformation);

        /**
         * Draws the main character
         * @param model: The instance of Model
         * @param transformation: The instance of Transformation
         */
        void drawMC(const std::shared_ptr<TH::Model>& model,
                    const std::shared_ptr<singleton::Transformation>& transformation);

        /**
         * Draws the AI
         * @param model: The instance of Model
         * @param transformation: The instance of Transformation
         */
        void drawAI(const std::shared_ptr<TH::Model>& model,
                    const std::shared_ptr<singleton::Transformation>& transformation);

        /**
         * Draws the backgrounds
         * @param model: The instance of Model
         * @param transformation: The instance of Transformation
         */
        void drawBackgrounds(const std::shared_ptr<TH::Model>& model,
                             const std::shared_ptr<singleton::Transformation>& transformation);

        /**
         * Draws every entity that the model requires to be drawn
         * @param model: The instance of Model
         * @param gameTime: The current game time
         * @param finishLineGenerated: boolean value indicating if the finish line has been generated
         * @param startCountdown: boolean value indicating if the start count down should be initiated
         * @param lookAhead: boolean value indicating if the look ahead of the AI should be drawn
         */
        void draw(const std::shared_ptr<TH::Model>& model, float gameTime, bool finishLineGenerated = false,
                  bool startCountdown = false, bool lookAhead = false);

        /**
         * Scrolls through the available background textures
         * @param bgSkin: Index of the current background texture chosen
         * @param scrollLeft: True if left key is pressed
         * @return The index of the newly chosen texture
         */
        int changeBackground(int& bgSkin, const bool& scrollLeft);

        /**
         * Scrolls through the available character textures
         * @param mcSkin: Index of the currently chosen texture
         * @param scrollDown: True if down key is pressed
         * @return Index of the newly chosen texture
         */
        int changeMcSkin(int& mcSkin, const bool& scrollDown);

        /**
         * Returns the correct key pressed during character loading screen
         * @return key pressed
         */
        Input getSkinInput();
};
} // namespace SFML
} // namespace TH

#endif // TURBOHIKER_VIEW_H
