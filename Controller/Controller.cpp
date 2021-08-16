//
// Created by JOHN CHRISTIAN CASTILLO on 7/18/2021.
//

#include "Controller.h"
TH::Controller::Controller(float fps) : fps(fps)
{
        // Initialize transformation instance
        float screenHeight = float(sf::VideoMode::getDesktopMode().height) * 0.75f;
        float screenWidth = screenHeight / 8.f * 6.f;
        std::shared_ptr<singleton::Transformation> transformation =
            singleton::Transformation::init(Dimensions{screenWidth, screenHeight});

        scoringSystem = std::make_shared<OBSERVER::LiveScoring>();
        model = std::make_shared<Model>(fps, scoringSystem);
        view = std::make_shared<SFML::View>(fps, model);
}
void TH::Controller::resetObjects()
{
        scoringSystem = std::make_shared<OBSERVER::LiveScoring>();
        model = std::make_shared<Model>(fps, scoringSystem);
        view = std::make_shared<SFML::View>(fps, model);
}
void TH::Controller::pollForEndScreen(bool& stillOnEndScreen, bool& stillOnStartScreen, bool& finishLineGenerated,
                                      std::shared_ptr<singleton::Timer>& timer)
{
        while (stillOnEndScreen) {
                if (view->pollEvent() == ZERO) {
                        return;
                }
                inputs = view->getKeyboardInput();
                for (const auto& in : inputs) {
                        if (view->pollEvent() == ZERO)
                                return;
                        if (in == ENTER) {
                                resetObjects();
                                timer->restart();
                                timer->resetGameTime();
                                view->draw(model, timer->getGameTime());
                                stillOnEndScreen = false;
                                finishLineGenerated = false;
                                stillOnStartScreen = true;
                        }
                }
                timer->restart();
                timer->resetGameTime();
        }
}
void TH::Controller::pollForStartScreen(bool& stillOnStartScreen, std::shared_ptr<singleton::Timer>& timer)
{
        if (stillOnStartScreen) {
                view->startScreen();
                while (stillOnStartScreen) {
                        if (view->pollEvent() == ZERO) {
                                return;
                        }
                        inputs = view->getKeyboardInput();
                        for (const auto& in : inputs) {
                                if (in == ENTER) {
                                        timer->restart();
                                        timer->resetGameTime();
                                        while (timer->getGameTime() <= 3) {
                                                timer->tick();
                                                timer->restart();
                                                // we start the countDown
                                                view->draw(model, 3 - timer->getGameTime(), false, true);
                                                timer->incrementGameTime(timer->getElapsedtime());
                                        }
                                        timer->restart();
                                        timer->resetGameTime();
                                        stillOnStartScreen = false;
                                }
                        }
                }
        }
}
bool TH::Controller::getKeyboardInput(const float& elapsedTime)
{
        inputs = view->getKeyboardInput();
        std::shared_ptr<MainCharacter> mc = model->getMainCharacter();
        bool moved{false};
        // We always move the AI up
        model->setSimpleAIMove(Move(0, -model->getSimpleAI()->getMovementSpeed() * elapsedTime));
        for (const auto& in : inputs) {
                switch (in) {
                case UP:
                        model->setBackgroundMove(Move(0, mc->getMovementSpeed() * elapsedTime));
                        moved = true;
                        break;
                case DOWN:
                        model->setBackgroundMove(Move(0, -mc->getMovementSpeed() * elapsedTime));
                        moved = true;
                        break;
                case LEFT:
                        model->setPlayerMove(Move(-mc->getMovementSpeed() * elapsedTime, 0));
                        moved = true;
                        break;
                case RIGHT:
                        model->setPlayerMove(Move(mc->getMovementSpeed() * elapsedTime, 0));
                        moved = true;
                        break;
                case HONKING:
                        model->getMainCharacter()->setYelling(true);
                        std::cout << "MC is Yelling at the enemy \n";
                        break;
                case SCARING:
                        model->getMainCharacter()->setScareEnemy(true);
                        std::cout << "MC is scaring the enemy \n";
                        break;
                default:
                        break;
                }
        }
        if (moved) {
                return true;
        }
        return false;
}
void TH::Controller::run()
{
        std::shared_ptr<singleton::Timer> timer = singleton::Timer::getInstance();
        view->startScreen();
        bool stillOnStartScreen{true};
        bool stillOnEndScreen{false};
        bool finishLineGenerated = false;
        while (view->getWindow().isOpen()) {
                // poll for End screen if we finished
                pollForEndScreen(stillOnEndScreen, stillOnStartScreen, finishLineGenerated, timer);
                // poll for Enter on start screen if we just started the game
                pollForStartScreen(stillOnStartScreen, timer);

                timer->tick();
                float elapsedTime = timer->getElapsedtime();
                if (timer->getElapsedtime() >= 1 / model->getFps()) {
                        timer->restart();
                        /// poll event
                        if (view->pollEvent() == ZERO)
                                return;

                        /// get keyboard input
                        /// if the player is moved then we want to first check for collisions
                        if (getKeyboardInput(elapsedTime)) {
                                if (timer->getGameTime() > 30 and !finishLineGenerated) {
                                        finishLineGenerated = true;
                                        model->generateFinishLine();
                                }
                                model->moveEntitiesExceptAI();
                        }
                }
                model->moveSimpleAI();
                // make sure player doesn't get off the screen;
                model->screenCollisionControl();
                // perform collision control and at the same time check if we collided with the finish line
                // if the finish line has been generated
                if (model->collisionControl(finishLineGenerated)) {
                        view->endScreen(model->getScoringSystem());
                        stillOnEndScreen = true;
                        continue;
                }
                model->resetMoves();
                view->draw(model, timer->getGameTime(), finishLineGenerated);
                timer->incrementGameTime(elapsedTime);
        }
}
