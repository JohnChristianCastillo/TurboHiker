//
// Created by JOHN CHRISTIAN CASTILLO on 7/18/2021.
//

#include "View.h"
const sf::RenderWindow& TH::SFML::View::getWindow() const { return window; }
void TH::SFML::View::initScoringSystem()
{
        retro.loadFromFile("../assets/fonts/Retro Gaming.ttf");
        scoreText.setCharacterSize(20);
        scoreText.setFont(retro);
        scoreText.setString("0");
        scoreText.setFillColor(sf::Color::Black);
        scoreText.setOrigin(scoreText.getGlobalBounds().width / 2, scoreText.getGlobalBounds().height / 2);
        scoreText.setPosition(screenWidth - 200, 10);
}
void TH::SFML::View::drawScore(const std::shared_ptr<OBSERVER::LiveScoring>& scoringSystem, const float& gameTime,
                               const float& scareCoolDown)

{
        scoreText.setString(std::to_string(scoringSystem->getScore()) + "\n" + std::to_string(gameTime) +
                            "\nScare\nCooldown: " + std::to_string(scareCoolDown));
        window.draw(scoreText);
}
TH::SFML::View::View(const float fps, const std::shared_ptr<TH::Model>& model)
{

        window.setFramerateLimit(static_cast<unsigned int>(fps));

        // initialize the player
        std::shared_ptr<singleton::Transformation> transformation = singleton::Transformation::getInstance();
        Dimensions playerDim =
            transformation->modelDimToViewDim(model->getMainCharacter()->getGlobalBounds()->dimensions);

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
void TH::SFML::View::loadTextures()
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
void TH::SFML::View::assignBGandMCTextures()
{
        backgroundImage1.setScale(static_cast<float>(screenWidth) / static_cast<float>(backgroundTexture.getSize().x),
                                  static_cast<float>(screenHeight) / static_cast<float>(backgroundTexture.getSize().y));
        backgroundImage2.setScale(static_cast<float>(screenWidth) / static_cast<float>(backgroundTexture.getSize().x),
                                  static_cast<float>(screenHeight) / static_cast<float>(backgroundTexture.getSize().y));
        backgroundImage3.setScale(static_cast<float>(screenWidth) / static_cast<float>(backgroundTexture.getSize().x),
                                  static_cast<float>(screenHeight) / static_cast<float>(backgroundTexture.getSize().y));
        backgroundImage1.setTexture(backgroundTexture);
        backgroundImage2.setTexture(backgroundTexture);
        backgroundImage3.setTexture(backgroundTexture);

        carSprite.setTexture(&carTexture);

        sf::RectangleShape finishObject(sf::Vector2f(screenWidth, 60));
        finishSprite = std::move(finishObject);
        finishSprite.setTexture(&finishLineTexture);
        finishSprite.setScale(static_cast<float>(screenWidth) * 2 / static_cast<float>(finishLineTexture.getSize().x),
                              static_cast<float>(screenHeight) /
                                  (15 * static_cast<float>(finishLineTexture.getSize().y)));
}
TH::Input TH::SFML::View::pollEvent()
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
                case sf::Event::KeyReleased:
                        if (event.key.code == sf::Keyboard::Up) {
                                upIsPressed = false;
                        } else if (event.key.code == sf::Keyboard::Down) {
                                downIsPressed = false;
                        } else if (event.key.code == sf::Keyboard::Left) {
                                leftIsPressed = false;
                        } else if (event.key.code == sf::Keyboard::Right) {
                                rightIsPressed = false;
                        }
                default:
                        return {};
                }
        }
        return {};
}
std::vector<TH::Input> TH::SFML::View::getKeyboardInput()
{
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
                return {Input::ENTER};
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                leftIsPressed = false;
                rightIsPressed = true;
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
std::vector<TH::Input> TH::SFML::View::produceKeyboardOutput()
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
void TH::SFML::View::endScreen(const std::shared_ptr<OBSERVER::LiveScoring>& pointingSystem)
{
        float score = pointingSystem->getScore();
        float highScore = pointingSystem->getHighScore();
        sf::Text endText;
        endText.setCharacterSize(20);
        endText.setFont(retro);
        endText.setString("HIGH SCORE: " + std::to_string(highScore) + "\nYOUR SCORE: " + std::to_string(score));
        endText.setFillColor(sf::Color::White);
        endText.setPosition(screenWidth / 2, screenHeight / 2);
        endText.setOrigin(endText.getLocalBounds().left + endText.getLocalBounds().width / 2.0f,
                          endText.getLocalBounds().top + endText.getLocalBounds().height / 2.0f);

        window.draw(endText);
        window.display();
        window.clear();
}
void TH::SFML::View::countDown(bool startCountDown, float time)
{
        if (startCountDown) {
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
void TH::SFML::View::startScreen()
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
void TH::SFML::View::drawLookAhead(const bool& lookAhead, const std::shared_ptr<TH::Model>& model,
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
void TH::SFML::View::drawEnemies(const std::shared_ptr<TH::Model>& model,
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
void TH::SFML::View::drawPowerUps(const std::shared_ptr<TH::Model>& model,
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
void TH::SFML::View::drawFinishLine(bool finishLineGenerated, const std::shared_ptr<TH::Model>& model,
                                    const std::shared_ptr<singleton::Transformation>& transformation)
{
        if (finishLineGenerated) {
                std::tuple<float, float> finishLineCoords =
                    transformation->modelToView(model->getFinishLine()->getGlobalBounds());
                finishSprite.setPosition(std::get<0>(finishLineCoords), std::get<1>(finishLineCoords));
                window.draw(finishSprite);
        }
}
void TH::SFML::View::drawInvincibilityPrompt(const std::shared_ptr<TH::Model>& model)
{
        if (model->getMainCharacter()->isInvincible()) {
                sf::Text startText;
                startText.setCharacterSize(20);
                startText.setFont(retro);
                startText.setString("INVINCIBLE!! " + std::to_string(static_cast<int>(
                                                          model->getMainCharacter()->getInvincibilityDuration())));
                startText.setFillColor(sf::Color::Yellow);
                startText.setOrigin(startText.getLocalBounds().left + startText.getLocalBounds().width / 2.0f,
                                    startText.getLocalBounds().top + startText.getLocalBounds().height / 2.0f);
                startText.setPosition(screenWidth / 2, screenHeight / 2);

                window.draw(startText);
        }
}
void TH::SFML::View::drawMC(const std::shared_ptr<TH::Model>& model,
                            const std::shared_ptr<singleton::Transformation>& transformation)
{
        std::tuple<float, float> carCoords = transformation->modelToView(model->getMainCharacter()->getGlobalBounds());
        view.setCenter(position); // center camera on position
        carSprite.setPosition(std::get<0>(carCoords), std::get<1>(carCoords));
        window.draw(carSprite);
}
void TH::SFML::View::drawAI(const std::shared_ptr<TH::Model>& model,
                            const std::shared_ptr<singleton::Transformation>& transformation)
{
        sf::RectangleShape simpleAISprite(sf::Vector2f(30, 60));
        simpleAISprite.setTexture(&enemyTextures[model->getSimpleAI()->getSkin()]);
        std::tuple<float, float> simpleAiCoords = transformation->modelToView(model->getSimpleAI()->getGlobalBounds());
        simpleAISprite.setPosition(std::get<0>(simpleAiCoords), std::get<1>(simpleAiCoords));
        window.draw(simpleAISprite);
}
void TH::SFML::View::drawBackgrounds(const std::shared_ptr<TH::Model>& model,
                                     const std::shared_ptr<singleton::Transformation>& transformation)
{
        std::tuple<float, float> bg1 = transformation->modelToView(model->getBackgrounds()[0]->getGlobalBounds());
        std::tuple<float, float> bg2 = transformation->modelToView(model->getBackgrounds()[1]->getGlobalBounds());
        std::tuple<float, float> bg3 = transformation->modelToView(model->getBackgrounds()[2]->getGlobalBounds());
        backgroundImage1.setPosition(std::get<0>(bg1), std::get<1>(bg1));
        backgroundImage2.setPosition(std::get<0>(bg2), std::get<1>(bg2));
        backgroundImage3.setPosition(std::get<0>(bg3), std::get<1>(bg3));
        window.draw(backgroundImage1);
        window.draw(backgroundImage2);
        window.draw(backgroundImage3);
}
void TH::SFML::View::draw(const std::shared_ptr<TH::Model>& model, float gameTime, bool finishLineGenerated,
                          bool startCountdown, bool lookAhead)
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

        drawScore(model->getScoringSystem(), gameTime, model->getMainCharacter()->getScareCoolDown());

        drawInvincibilityPrompt(model);

        countDown(startCountdown, gameTime);

        window.display();
        window.clear();
}
