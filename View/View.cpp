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
        scoreText.setPosition(screenWidth - 220, 10);
}
void TH::SFML::View::drawScore(const std::shared_ptr<OBSERVER::LiveScoring>& scoringSystem, const float& gameTime,
                               const float& scareCoolDown, const bool& canSpawnEnemy)
{
        if (canSpawnEnemy) {
                scoreText.setString(
                    std::to_string(static_cast<int>(scoringSystem->getScore())) + "\n" + std::to_string(gameTime) +
                    "\nScare\nCooldown: " + std::to_string(static_cast<int>(scareCoolDown)) + "\nSpawn Enemy: Yes");
        } else {
                scoreText.setString(
                    std::to_string(static_cast<int>(scoringSystem->getScore())) + "\n" + std::to_string(gameTime) +
                    "\nScare\nCooldown: " + std::to_string(static_cast<int>(scareCoolDown)) + "\nSpawn Enemy: No");
        }

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
        // initialize to cover the whole screen
        view.reset(sf::FloatRect(0, 0, screenWidth, screenHeight));
        // how much of the view we want to see
        view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
        initScoringSystem();
}
void TH::SFML::View::loadTextures()
{
        // if (!backgroundTexture.loadFromFile("../assets/1.png")) {

        sf::Texture tempBgTexture{};
        for (int i = 1; i <= 7; ++i) {
                std::string fileLocation = "../assets/Roads/" + std::to_string(i) + ".png";
                if (!tempBgTexture.loadFromFile(fileLocation)) {
                        std::cerr << "bg img not found" << std::endl;
                }
                backgroundTextures.push_back(tempBgTexture);
        }

        if (!finishLineTexture.loadFromFile("../assets/finishLine.png")) {
                std::cerr << "finish line image not found" << std::endl;
        }

        if (!invincibilityStarTexture.loadFromFile("../assets/invincibilityStar.png")) {
                std::cerr << "invincibility star image not found" << std::endl;
        }
        if (!speedBoostTexture.loadFromFile("../assets/arrow_yellow.png")) {
                std::cerr << "speedboost image not found" << std::endl;
        }
        if (!summonEnemyTexture.loadFromFile("../assets/spawnPowerUp.png")) {
                std::cerr << "spawnPowerUp image not found" << std::endl;
        }
        if (!nukeTexture.loadFromFile("../assets/nuke.png")) {
                std::cerr << "nuke image not found" << std::endl;
        }
        if (!laserBeamTexture.loadFromFile("../assets/laserBeam.png")) {
                std::cerr << "spawnPowerUp image not found" << std::endl;
        }

        sf::Texture tempTure{};
        for (int i = 1; i <= 17; ++i) {
                std::string fileLocation = "../assets/cars/" + std::to_string(i) + ".png";
                if (!tempTure.loadFromFile(fileLocation)) {
                        std::cerr << "bg img not found" << std::endl;
                }
                enemyTextures.push_back(tempTure);
        }
}
void TH::SFML::View::assignBGandMCTextures(const int& bgIndex, const int& mcIndex)
{

        backgroundImage1.setScale(
            static_cast<float>(screenWidth) / static_cast<float>(backgroundTextures[bgIndex].getSize().x),
            static_cast<float>(screenHeight) / static_cast<float>(backgroundTextures[bgIndex].getSize().y));
        backgroundImage2.setScale(
            static_cast<float>(screenWidth) / static_cast<float>(backgroundTextures[bgIndex].getSize().x),
            static_cast<float>(screenHeight) / static_cast<float>(backgroundTextures[bgIndex].getSize().y));
        backgroundImage3.setScale(
            static_cast<float>(screenWidth) / static_cast<float>(backgroundTextures[bgIndex].getSize().x),
            static_cast<float>(screenHeight) / static_cast<float>(backgroundTextures[bgIndex].getSize().y));
        backgroundImage1.setTexture(backgroundTextures[bgIndex]);
        backgroundImage2.setTexture(backgroundTextures[bgIndex]);
        backgroundImage3.setTexture(backgroundTextures[bgIndex]);

        carSprite.setTexture(&enemyTextures[mcIndex]);

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
                        break;
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
        }
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
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
                wantsToSpawnEnemy = true;
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
        if (wantsToSpawnEnemy) {
                retVect.push_back(Input::SPAWNENEMY);
                wantsToSpawnEnemy = false;
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
        endText.setString("YOU FINISHED: " + pointingSystem->getPosition() +
                          "\nHIGH SCORE: " + std::to_string(static_cast<int>(highScore)) +
                          "\nYOUR SCORE: " + std::to_string(static_cast<int>(score)));
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

        sf::Text optionText;
        optionText.setCharacterSize(20);
        optionText.setFont(retro);
        optionText.setString("\n(OPTIONAL)"
                             "\nchoose background: LEFT or RIGHT arrow key"
                             "\nchoose character: UP or DOWN arrow key");

        optionText.setFillColor(sf::Color::White);
        optionText.setOrigin(optionText.getLocalBounds().left + optionText.getLocalBounds().width / 2.0f,
                             optionText.getLocalBounds().top + optionText.getLocalBounds().height);
        optionText.setPosition(screenWidth / 2, screenHeight - 50);

        window.draw(optionText);
        window.draw(startText);
        window.display();
        window.clear();
}
void TH::SFML::View::drawLookAhead(const bool& lookAhead, const std::shared_ptr<TH::Model>& model,
                                   const std::shared_ptr<singleton::Transformation>& transformation)
{
        if (lookAhead) {
                for (const auto& ai : model->getSimpleAI()) {
                        for (const auto& i : ai->getLookAhead()) {
                                std::tuple<float, float> auraPos = transformation->modelToView(i);
                                /// Collision object
                                sf::RectangleShape nextBox{sf::Vector2f(carSprite.getSize())};
                                nextBox.setFillColor(sf::Color::Transparent);
                                nextBox.setOutlineColor(sf::Color::White);
                                nextBox.setOutlineThickness(3.f);
                                nextBox.setPosition(std::get<0>(auraPos), std::get<1>(auraPos));
                                window.draw(nextBox);
                        }
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
                } else if (powerUp->getType() == EntityTypes::summonEnemy) {
                        wallSprite.setTexture(&summonEnemyTexture);
                } else if (powerUp->getType() == EntityTypes::nukePowerUp) {
                        wallSprite.setTexture(&nukeTexture);
                } else if (powerUp->getType() == EntityTypes::laserBeamPowerUp) {
                        wallSprite.setTexture(&laserBeamTexture);
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

void TH::SFML::View::drawLaserBeamAndPrompt(const std::shared_ptr<TH::Model>& model,
                                            const std::shared_ptr<singleton::Transformation>& transformation)
{
        if (model->getMainCharacter()->isLaserActive()) {
                sf::Text startText;
                startText.setCharacterSize(20);
                startText.setFont(retro);
                startText.setString("LASER!! " + std::to_string(static_cast<int>(
                                                     model->getMainCharacter()->getInvincibilityDuration())));
                startText.setFillColor(sf::Color::Yellow);
                startText.setOrigin(startText.getLocalBounds().left + startText.getLocalBounds().width / 2.0f,
                                    startText.getLocalBounds().top + startText.getLocalBounds().height / 2.0f);
                startText.setPosition(screenWidth / 2, (screenHeight / 2) + 20);

                window.draw(startText);

                Dimensions dim =
                    transformation->modelDimToViewDim(model->getMainCharacter()->getLaserBeamBounds()[0]->dimensions);
                for (const auto& i : model->getMainCharacter()->getLaserBeamBounds()) {
                        std::tuple<float, float> auraPos = transformation->modelToView(i);
                        /// Collision object
                        /// Next box visualization todo: remove for final
                        sf::RectangleShape nextBox{sf::Vector2f(dim.width, dim.height)};
                        sf::Color color = sf::Color::Red;
                        color.a = 128;
                        nextBox.setFillColor(color);
                        nextBox.setPosition(std::get<0>(auraPos), std::get<1>(auraPos));
                        window.draw(nextBox);
                        window.draw(nextBox);
                }
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
        for (auto& ai : model->getSimpleAI()) {
                sf::RectangleShape simpleAISprite(sf::Vector2f(30, 60));
                simpleAISprite.setTexture(&enemyTextures[ai->getSkin()]);
                std::tuple<float, float> simpleAiCoords = transformation->modelToView(ai->getGlobalBounds());
                simpleAISprite.setPosition(std::get<0>(simpleAiCoords), std::get<1>(simpleAiCoords));
                window.draw(simpleAISprite);
        }
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

        drawScore(model->getScoringSystem(), gameTime, model->getMainCharacter()->getScareCoolDown(),
                  model->getMainCharacter()->canSummonEnemy());

        drawInvincibilityPrompt(model);

        drawLaserBeamAndPrompt(model, transformation);

        countDown(startCountdown, gameTime);

        window.display();
        window.clear();
}
int TH::SFML::View::changeBackground(int& bgSkin, const bool& scrollLeft)
{
        demoBG = sf::Sprite();
        window.clear();
        if (scrollLeft) {
                --bgSkin;
        } else if (!scrollLeft) {
                ++bgSkin;
        }

        if (bgSkin < 0) {
                bgSkin = 6;
        } else if (bgSkin > 6) {
                bgSkin = 0;
        }

        int retSkin = std::abs(bgSkin % static_cast<int>(backgroundTextures.size()));
        demoBG.setScale(static_cast<float>(screenWidth) / static_cast<float>(backgroundTextures[retSkin].getSize().x),
                        static_cast<float>(screenHeight) / static_cast<float>(backgroundTextures[retSkin].getSize().y));
        demoBG.setTexture(backgroundTextures[retSkin]);
        window.draw(demoBG);
        window.draw(demoCar);
        window.display();
        return retSkin;
}
int TH::SFML::View::changeMcSkin(int& mcSkin, const bool& scrollDown)
{
        demoCar = sf::RectangleShape(sf::Vector2f(30, 60));
        window.clear();

        if (scrollDown) {
                --mcSkin;
        } else if (!scrollDown) {
                ++mcSkin;
        }
        if (mcSkin < 0) {
                mcSkin = 16;
        } else if (mcSkin > 16) {
                mcSkin = 0;
        }

        int retSkin = std::abs(mcSkin % static_cast<int>(enemyTextures.size()));
        demoCar.setTexture(&enemyTextures[retSkin]);
        demoCar.setPosition(screenWidth / 2, (screenHeight / 2) + 30);
        window.draw(demoBG);
        window.draw(demoCar);
        window.display();
        return retSkin;
}
TH::Input TH::SFML::View::getSkinInput()
{
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) and !rightIsPressed) {
                rightIsPressed = true;
                return Input::RIGHT;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) and !leftIsPressed) {
                leftIsPressed = true;
                return Input::LEFT;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) and !upIsPressed) {
                upIsPressed = true;
                return Input::UP;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) and !downIsPressed) {
                downIsPressed = true;
                return Input::DOWN;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
                return Input::ENTER;
        }
        return Input::HONKING; // arbitrary return
}