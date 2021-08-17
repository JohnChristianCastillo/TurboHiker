//
// Created by JOHN CHRISTIAN CASTILLO on 7/18/2021.
//

#include "Model.h"

TH::Model::Model(float frameLimit, const std::weak_ptr<OBSERVER::LiveScoring>& scoringObserver)
    : fps(frameLimit), scoringSystem(scoringObserver)
{
        entityFactory = std::make_shared<EntityMaker>();

        enemies = std::move(generateEnemies());
        mainCharacter = generateMC();
        simpleAi = generateAI();
        backgrounds = generateBackground();
        scoringSystem = std::make_shared<OBSERVER::LiveScoring>();
}

float TH::Model::getFps() const { return fps; }
void TH::Model::setPlayerMove(const Move& move) { Model::playerMove = move; }
void TH::Model::setBackgroundMove(const Move& move) { Model::backgroundMove = move; }
const std::shared_ptr<TH::OBSERVER::LiveScoring>& TH::Model::getScoringSystem() const { return scoringSystem; }
void TH::Model::setSimpleAIMove(const Move& move) { Model::simpleAiMove = move; }
std::shared_ptr<TH::MainCharacter> TH::Model::getMainCharacter() const { return mainCharacter; }
std::shared_ptr<TH::Finish> TH::Model::getFinishLine() const { return finishLine; }
std::shared_ptr<TH::SimpleAI> TH::Model::getSimpleAI() const { return simpleAi; }
std::vector<std::shared_ptr<TH::Background>> TH::Model::getBackgrounds() const { return backgrounds; }
std::vector<std::shared_ptr<TH::Enemy>> TH::Model::getEnemies()
{
        if (enemies.empty()) {
                enemies = entityFactory->generateEnemies();
        }
        return enemies;
}
std::vector<std::shared_ptr<TH::PowerUp>> TH::Model::getPowerUps()
{
        if (powerUps.empty()) {
                powerUps = entityFactory->generatePowerUp();
        }
        return powerUps;
}
void TH::Model::generateFinishLine() { finishLine = entityFactory->generateFinishLine(); }
std::shared_ptr<TH::MainCharacter> TH::Model::generateMC() { return entityFactory->generateMainCharacter(lanes); }
std::shared_ptr<TH::SimpleAI> TH::Model::generateAI() { return entityFactory->generateAI(); }
std::vector<std::shared_ptr<TH::Background>> TH::Model::generateBackground()
{
        return entityFactory->generateBackground();
}
std::vector<std::shared_ptr<TH::Enemy>> TH::Model::generateEnemies()
{
        // we can't just assign the generated enemies directly to our enemies container since enemies can be
        // not empty
        std::vector<std::shared_ptr<Enemy>> generatedEnemies = entityFactory->generateEnemies();
        for (std::shared_ptr<Enemy>& enemy : generatedEnemies) {
                enemies.push_back(std::move(enemy));
        }
        return enemies;
}
std::vector<std::shared_ptr<TH::PowerUp>> TH::Model::generatePowerUps()
{
        // we can't just assign the generated enemies directly to our enemies container since enemies can be
        // not empty
        std::vector<std::shared_ptr<PowerUp>> generatedPowerUps = entityFactory->generatePowerUp();
        for (std::shared_ptr<PowerUp>& powerUp : generatedPowerUps) {
                powerUps.push_back(std::move(powerUp));
        }
        return powerUps;
}
void TH::Model::resetMoves()
{
        playerMove = {};
        backgroundMove = {};
        simpleAiMove = {};
}
void TH::Model::moveSimpleAI()
{
        simpleAi->move(simpleAiMove.x, (simpleAiMove.y * simpleAi->getSlowingFactor() +
                                        backgroundMove.y * mainCharacter->getSlowingFactor()));
        if (simpleAi->isSlowed()) {
                simpleAi->reduceSlowingEffect(simpleAi->getSlowingFactor() + 0.02f);
        }
        if (simpleAi->isSped()) {
                simpleAi->reduceSpeedBoostEffect(simpleAi->getSlowingFactor() - 0.01f);
        }
}
void TH::Model::moveBackground()
{
        Position bg1Pos = backgrounds[0]->getGlobalBounds()->position;
        Position bg2Pos = backgrounds[1]->getGlobalBounds()->position;
        Position mcPos = mainCharacter->getGlobalBounds()->position;
        if (bg1Pos.y > mcPos.y) {
                backgrounds[2]->setPosition(bg1Pos.x, bg1Pos.y);
                backgrounds[0]->setPosition(bg1Pos.x,
                                            bg1Pos.y - backgrounds[0]->getGlobalBounds()->dimensions.height * 2);
        } else if (bg2Pos.y > mcPos.y) {
                backgrounds[2]->setPosition(bg2Pos.x, bg2Pos.y);
                backgrounds[1]->setPosition(bg2Pos.x,
                                            bg2Pos.y - backgrounds[1]->getGlobalBounds()->dimensions.height * 2);
        }
        for (const auto& bg : backgrounds) {
                bg->move(backgroundMove.x, backgroundMove.y * mainCharacter->getSlowingFactor());
        }
        if (mainCharacter->isSlowed()) {
                mainCharacter->reduceSlowingEffect(mainCharacter->getSlowingFactor() + 0.01f);
        } else if (mainCharacter->isSped()) {
                mainCharacter->reduceSpeedBoostEffect(mainCharacter->getSlowingFactor() - 0.005f);
        }
}
void TH::Model::moveEnemies()
{
        if (enemies.empty()) {
                generateEnemies();
        }
        // generate new enemies if last generated enemy is past half the screen;
        if (enemies.back()->getGlobalBounds()->position.y >= 4.f) {
                generateEnemies();
        }

        for (int i = enemies.size() - 1; i >= 0; --i) {
                std::shared_ptr<Enemy> enemy = enemies[i];

                float movement = backgroundMove.y * enemy->getMovementSpeed() * (mainCharacter->getSlowingFactor());

                if (enemy->isSteerRandolmy()) {
                        steerRandomly(enemy);
                } else if (enemy->getGlobalBounds()->position.y >= 9.f) {
                        // remove enemies outside of scope
                        enemies.erase(enemies.begin() + i);
                } else {
                        // we first need to identify if it's a left to right hiker or a simple static hiker
                        //  advance ai at normal speed even if mc is slowed;
                        if (enemy->isSlowed()) {
                                if (enemy->getType() == EntityTypes::leftToRightHiker) {
                                        enemy->move(movement, movement);
                                        enemy->reduceSlowingEffect(enemy->getSlowingFactor() + 0.1f);
                                } else {
                                        enemy->move(0, movement);
                                        enemy->reduceSlowingEffect(enemy->getSlowingFactor() + 0.1f);
                                }

                        } else {
                                if (enemy->getType() == EntityTypes::leftToRightHiker) {
                                        enemy->move(movement, movement);
                                } else {
                                        enemy->move(0, movement);
                                }
                        }
                }
        }
}
void TH::Model::movePowerUps()
{
        // generate new enemies if last generated enemy is past half the screen;
        if (powerUps.empty()) {
                generatePowerUps();
        } else if (!powerUps.empty()) {
                if (powerUps.back()->getGlobalBounds()->position.y >= 4.f) {
                        generatePowerUps();
                }
        }

        for (int i = powerUps.size() - 1; i >= 0; --i) {
                std::shared_ptr<PowerUp> powerUp = powerUps[i];

                float movement = backgroundMove.y * mainCharacter->getSlowingFactor();
                if (powerUp->getGlobalBounds()->position.y >= 9.f) {
                        // remove enemies outside of scope
                        powerUps.erase(powerUps.begin() + i);
                }

                else {
                        powerUp->move(0, movement);
                }
        }
}
void TH::Model::moveEntitiesExceptAI()
{
        moveMC();
        moveBackground();
        moveEnemies();
        movePowerUps();
}
void TH::Model::steerRandomly(const std::shared_ptr<Enemy>& enemy)
{
        Move enemyMove = backgroundMove;
        std::shared_ptr<singleton::Random> random = singleton::Random::getInstance();
        std::vector<Input> direction{Input::LEFT, Input::RIGHT};
        int index = random->intInInterval(0, 1);
        switch (direction[index]) {
        case LEFT:
                enemyMove.y = 0;
                if (enemyMove.x == 0) {
                        enemyMove.x -= 0.2f;
                }
                break;
        case RIGHT:
                enemyMove.y = 0;
                if (enemyMove.x == 0) {
                        enemyMove.x += 0.2f;
                }
                break;
        default:
                break;
        }
        enemy->move(enemyMove.x, enemyMove.y);
        enemy->setSteerRandolmy(false);
}
void TH::Model::screenCollisionControl()
{
        Position mcPos = mainCharacter->getGlobalBounds()->position;
        Dimensions mcDim = mainCharacter->getGlobalBounds()->dimensions;
        /// Window collision control
        /// left collision
        if (mcPos.x - (mcDim.width / 2) <= 0) {
                mainCharacter->setPosition(mcDim.width / 2, mainCharacter->getGlobalBounds()->position.y);
        }
        /// right collision
        if (mcPos.x + (mcDim.width / 2) >= 6.f) {
                mainCharacter->setPosition(6.f - (mcDim.width / 2), mcPos.y);
        }

        /// Window collision control
        Position aiPos = simpleAi->getGlobalBounds()->position;
        Dimensions aiDim = simpleAi->getGlobalBounds()->dimensions;
        /// left collision
        if (aiPos.x - (aiDim.width / 2) <= 0) {
                simpleAi->setPosition(aiDim.width / 2, simpleAi->getGlobalBounds()->position.y);
        }
        /// right collision
        if (aiPos.x + (aiDim.width / 2) >= 6.f) {
                simpleAi->setPosition(6.f - (aiDim.width / 2), aiPos.y);
        }
}
bool TH::Model::finishLineCollisionControl()
{
        if (finishLine->getGlobalBounds()->position.y > mainCharacter->getGlobalBounds()->position.y) {
                if (mainCharacter->getGlobalBounds()->position.y > simpleAi->getGlobalBounds()->position.y) {
                        scoringSystem->playerFinishedFirst();
                }
                return true;
        }
        finishLine->move(0, backgroundMove.y * mainCharacter->getSlowingFactor());
        return false;
}
void TH::Model::aiCollisionPrevention(const std::shared_ptr<Enemy>& enemy,
                                      const std::shared_ptr<GlobalBounds>& nextPosition)

{
        // initialize the lookahead our AI has;
        std::vector<std::shared_ptr<GlobalBounds>> simpleAILookAhead = simpleAi->getLookAhead();
        for (int j = 0; j <= 2; ++j) {
                // check whether the three frontal lookahead intersects with either the spawned enemy or the MC
                // if so warn our AI
                if (simpleAILookAhead[j]->intersects<float>(enemy->getGlobalBounds()) or
                    simpleAILookAhead[j]->intersects<float>(nextPosition)) {
                        enemyUp = true;
                        break;
                }
        }
        if (simpleAILookAhead[3]->intersects<float>(enemy->getGlobalBounds()) or
            simpleAILookAhead[3]->intersects<float>(nextPosition)) {
                enemyLeft = true;
        }
        if (simpleAILookAhead[4]->intersects<float>(enemy->getGlobalBounds()) or
            simpleAILookAhead[4]->intersects<float>(nextPosition)) {
                enemyRight = true;
        }
        // up left
        if (simpleAILookAhead[5]->intersects<float>(enemy->getGlobalBounds()) or
            simpleAILookAhead[5]->intersects<float>(nextPosition)) {
                enemyUpLeft = true;
        }
        // up right
        if (simpleAILookAhead[6]->intersects<float>(enemy->getGlobalBounds()) or
            simpleAILookAhead[6]->intersects<float>(nextPosition)) {
                enemyUpRight = true;
        }
}
void TH::Model::collisionWithEnemyControl(const std::shared_ptr<GlobalBounds>& nextPosition,
                                          const std::shared_ptr<GlobalBounds>& aiNextPosition)

{

        int originalEnemySize = static_cast<int>(enemies.size());
        for (int i = originalEnemySize - 1; i >= 0; --i) {
                if (enemies.empty()) {
                        break;
                }
                bool enemyDeleted{false};

                // check first if the main character has lase beams active, if so we check if this collides with
                // the currently being checked enemy. if so then we just remove the enemy without penalizing
                // the player
                if (mainCharacter->isLaserActive()) {
                        for (auto& laserBound : mainCharacter->getLaserBeamBounds()) {
                                if (enemies[i]->getGlobalBounds()->intersects<float>(laserBound)) {
                                        enemies.erase(enemies.begin() + i);
                                        scoringSystem->laseredEnemy();
                                        enemyDeleted = true;
                                        break;
                                }
                        }
                        if (enemyDeleted) {
                                continue;
                        }
                }

                // Try to prevent AI from colliding in the future
                aiCollisionPrevention(enemies[i], nextPosition);

                // The MC's area of effect is the whole screen
                // we need to know if our MC is scaring off enemy players, if so we add scarePoints to the
                // player This in turn causes the enemy to panic steer this scarePoint has a threshold and once
                // exceeded it can throw off the enemy
                if (mainCharacter->isScaringEnemy() and mainCharacter->getScareCoolDown() <= 0) {
                        if (enemies[i]->exceededScareThreshold()) {
                                enemies.erase(enemies.begin() + i);
                                scoringSystem->hikerThrownOff();
                                continue;
                        } else {
                                // if it hasn't exceeded the threshold yet, we will steer the enemy randomly
                                enemies[i]->setSteerRandolmy(true);
                                scoringSystem->hikerOffended();
                        }
                }

                if (enemies[i]->getGlobalBounds()->intersects<float>(nextPosition)) {
                        // if we collided we want to penalize our player by slowing it down and subtracting
                        // points unless our main character is invincible
                        if (!mainCharacter->isInvincible()) {
                                scoringSystem->crashed();
                                mainCharacter->slowDown();
                        }

                        enemies.erase(enemies.begin() + i);
                        continue;
                }

                if (enemies[i]->getGlobalBounds()->intersects<float>(aiNextPosition)) {
                        // if we collided we want to penalize our player by slowing it down and subtracting
                        // points
                        simpleAi->slowDown();
                        enemies.erase(enemies.begin() + i);
                }
        }
}
void TH::Model::collisionWithPowerUpControl(const std::shared_ptr<GlobalBounds>& nextPosition,
                                            const std::shared_ptr<GlobalBounds>& aiNextPosition)
{

        for (int i = powerUps.size() - 1; i >= 0; --i) {
                std::shared_ptr<PowerUp> powerUp = powerUps[i];

                if (powerUps[i]->getGlobalBounds()->intersects<float>(nextPosition)) {
                        // if we collided we want to check which powerup our player collided with;
                        if (powerUp->getType() == EntityTypes::speedUp) {
                                mainCharacter->speedUp();
                        } else if (powerUp->getType() == EntityTypes::invincibilityStar) {
                                mainCharacter->startInvincibility();
                        } else if (powerUp->getType() == EntityTypes::summonEnemy) {
                                mainCharacter->setSummonEnemy(true);
                        } else if (powerUp->getType() == EntityTypes::nukePowerUp) {
                                enemies = {};
                        } else if (powerUp->getType() == EntityTypes::laserBeamPowerUp) {
                                mainCharacter->startLaserBeam();
                        }
                        powerUps.erase(powerUps.begin() + i);
                        return; // to avoid multiple players picking up power up
                }
                if (powerUps[i]->getGlobalBounds()->intersects<float>(aiNextPosition)) {
                        // if we collided we want to check which powerup our player collided with;
                        if (powerUp->getType() == EntityTypes::speedUp) {
                                simpleAi->speedUp();
                        }
                        powerUps.erase(powerUps.begin() + i);
                }
        }
}
bool TH::Model::collisionControl(bool finishLineGenerated)
{
        if (finishLineGenerated) {
                if (finishLineCollisionControl()) {
                        return true;
                }
        }
        // first initialize the next position of our player;
        std::shared_ptr<GlobalBounds> nextPosition;
        std::shared_ptr<GlobalBounds> playerBounds = mainCharacter->getGlobalBounds();
        nextPosition = std::make_shared<GlobalBounds>(*playerBounds);
        nextPosition->position.x += (playerMove.x - backgroundMove.x);
        nextPosition->position.y += (playerMove.y - backgroundMove.y);

        // then initialize the next position of our AI;
        std::shared_ptr<GlobalBounds> aiNextPosition;
        std::shared_ptr<GlobalBounds> simpleAIBounds = simpleAi->getGlobalBounds();
        aiNextPosition = std::make_shared<GlobalBounds>(*simpleAIBounds);
        aiNextPosition->position.x += (simpleAiMove.x - backgroundMove.x);
        aiNextPosition->position.y += (simpleAiMove.y - backgroundMove.y);

        collisionWithPowerUpControl(nextPosition, aiNextPosition);
        collisionWithEnemyControl(nextPosition, aiNextPosition);

        simpleAi->randomMove(enemyUp, enemyLeft, enemyRight, enemyUpLeft, enemyUpRight, simpleAiMove.y, simpleAiMove.y);
        enemyLeft = false;
        enemyRight = false;
        enemyUp = false;
        enemyUpLeft = false;
        enemyUpRight = false;
        if (mainCharacter->isScaringEnemy() and mainCharacter->getScareCoolDown() <= 0) {
                simpleAi->slowDown();
                mainCharacter->resetScareCoolDown();
        }
        if (mainCharacter->isInvincible()) {
                mainCharacter->decreaseInvincibilityDuration(0.05);
        }
        if (mainCharacter->isLaserActive()) {
                mainCharacter->decreaseLaserBeamDuration(0.05);
        }
        mainCharacter->decrementScareCoolDown();

        mainCharacter->setScareEnemy(false);
        scoringSystem->advance();
        return false;
}
void TH::Model::spawnEnemy()
{
        if (mainCharacter->canSummonEnemy()) {
                std::shared_ptr<Enemy> summonedEnemy =
                    entityFactory->summonEnemy(mainCharacter->getGlobalBounds()->position);
                bool canSummon = true;
                for (const auto& enemy : enemies) {
                        if (enemy->getGlobalBounds()->intersects<float>(summonedEnemy->getGlobalBounds())) {
                                canSummon = false;
                        }
                }
                if (canSummon) {
                        enemies.push_back(summonedEnemy);
                }
                mainCharacter->setSummonEnemy(false);
        }
}
