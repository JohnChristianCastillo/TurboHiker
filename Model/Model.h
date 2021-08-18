//
// Created by JOHN CHRISTIAN CASTILLO on 7/18/2021.
//

#ifndef TURBOHIKER_MODEL_H
#define TURBOHIKER_MODEL_H

#include "../Observers/LiveScoring.h"
#include "../Singletons/Transformation.h"
#include "EnemyHikers/Enemy.h"
#include "EntityFactory/EntityMaker.h"
#include "MainCharacter.h"
#include <iostream>
#include <utility>
#include <vector>

namespace TH {
class Model
{
        int lanes{4};
        float fps;

        std::shared_ptr<EntityMaker> entityFactory;
        std::shared_ptr<MainCharacter> mainCharacter;
        std::vector<std::shared_ptr<SimpleAI>> simpleAi;
        std::shared_ptr<OBSERVER::LiveScoring> scoringSystem;
        std::vector<std::shared_ptr<Enemy>> enemies;
        std::vector<std::shared_ptr<Background>> backgrounds;
        std::shared_ptr<Finish> finishLine{nullptr};
        std::vector<std::shared_ptr<PowerUp>> powerUps;

        Move playerMove{};
        Move backgroundMove{};
        Move simpleAiMove{};

public:
        /**
         * Instantiates a model object and generates necessary entities with it
         * @param frameLimit: The fram rate of the users screen
         * @param scoringObserver: The pointing system object
         */
        explicit Model(float frameLimit, const std::weak_ptr<OBSERVER::LiveScoring>& scoringObserver);

        /**
         * @return The frame rate of the users screen
         */
        float getFps() const;

        /**
         * @param move: The factor that affects the movement of the player
         */
        void setPlayerMove(const Move& move);

        /**
         *
         * @param move: The factor that affects the movement of the background
         */
        void setBackgroundMove(const Move& move);

        /**
         * @param move: The factor that affects the movement of the player
         */
        void setSimpleAIMove(const Move& move);

        /**
         * @return The scoring system of the game
         */
        const std::shared_ptr<OBSERVER::LiveScoring>& getScoringSystem() const;

        /**
         * @return The main character
         */
        std::shared_ptr<MainCharacter> getMainCharacter() const;

        /**
         * @return The finish line
         */
        std::shared_ptr<Finish> getFinishLine() const;

        /**
         * @return The simple AI vector
         */
        std::vector<std::shared_ptr<SimpleAI>> getSimpleAI() const;

        /**
         * @return The vector of backgrounds
         */
        std::vector<std::shared_ptr<Background>> getBackgrounds() const;

        /**
         * @return The vector of enemies
         */
        std::vector<std::shared_ptr<Enemy>> getEnemies();

        /**
         * @return The vector of power ups
         */
        std::vector<std::shared_ptr<PowerUp>> getPowerUps();

        /**
         * Generates the finish line object with the help of EntityMaker
         */
        void generateFinishLine();

        /**
         * Generates the main character with the help of EntityMaker
         * @return The main character
         */
        std::shared_ptr<MainCharacter> generateMC();

        /**
         * Generates a simple AI with the help of EntityMaker
         * @return a vector of AI's
         */
        std::vector<std::shared_ptr<SimpleAI>> generateAI();

        /**
         * Generates a vector of backgrounds with the help of EntityMaker
         * @return
         */
        std::vector<std::shared_ptr<Background>> generateBackground();
        /**
         * Generates enemies of random types spawning them at the top part of the screen
         * @return A vector of generated enemies
         */
        std::vector<std::shared_ptr<Enemy>> generateEnemies();

        /**
         * Generates a vector of power ups with the help of EntityMaker
         * @return a vector of power ups
         */
        std::vector<std::shared_ptr<PowerUp>> generatePowerUps();

        /**
         * Resets the background, player and ai moves
         */
        void resetMoves();

        /**
         * Moves the main character
         */
        void moveMC() { mainCharacter->move(playerMove.x, playerMove.y); }

        /**
         * Moves the simple AI
         */
        void moveSimpleAI();

        /**
         * Moves the background entities
         */
        void moveBackground();

        /**
         * Moves the Enemy entities
         */
        void moveEnemies();

        /**
         * Moves the power up entities
         */
        void movePowerUps();

        /**
         * Moves every entity except the AI
         */
        void moveEntitiesExceptAI();

        /**
         * Steers an enemy randomly
         * @param enemy: The enemy we want to steer randomly
         */
        void steerRandomly(const std::shared_ptr<Enemy>& enemy);

        /**
         * Prevents the main character to steer off the screen
         */
        void screenCollisionControl();

        /**
         * Checks if the player has collided with the finish line and checks at which position it is relative to the
         * Enemy AI
         * @return True if the player crossed the finish line, false otherwise
         */
        bool finishLineCollisionControl();

        /**
         * Prevents (if possible) the AI from colliding with future obstacles, this is done by making use of auras
         * around it that senses if there are entities within the aura's range
         * @param enemy: The current enemy we are checking
         * @param nextPosition: The next position of our main character
         */
        void aiCollisionPrevention(const std::shared_ptr<Enemy>& enemy,
                                   const std::shared_ptr<GlobalBounds>& nextPosition);

        /**
         * Checks whether the AI or the main character has collided with its enemies
         * @param nextPosition: The next position of the main character
         * @param aiNextPosition: The next position of the AI
         */
        void collisionWithEnemyControl(const std::shared_ptr<GlobalBounds>& nextPosition,
                                       const std::vector<std::shared_ptr<GlobalBounds>>& aiNextPositions);

        /**
         * Checks whether the AI or the main character has collided with a power up
         * @param nextPosition: The next position of the main character
         * @param aiNextPosition: The next position of the AI
         */
        void collisionWithPowerUpControl(const std::shared_ptr<GlobalBounds>& nextPosition,
                                         const std::vector<std::shared_ptr<GlobalBounds>>& aiNextPositions);

        /**
         * This function checks collision between:
         * 1: The main character and (the enemy spawned together with the simple AI)
         * 2: The Simple AI and (the enemy spawned together with the main character)
         *
         * This combination is necessary to achieve only looping once through all the spawned enemy entities
         */
        bool collisionControl(bool finishLineGenerated);

        /**
         * Spawns an enemy if the main character can spawn an enemy
         */
        void spawnEnemy();
};
} // namespace TH

#endif // TURBOHIKER_MODEL_H
