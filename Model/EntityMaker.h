//
// Created by JOHN CHRISTIAN CASTILLO on 7/18/2021.
//

#ifndef TURBOHIKER_ENTITYMAKER_H
#define TURBOHIKER_ENTITYMAKER_H

#include "../Singletons/Random.h"
#include "Background.h"
#include "EnemyHikers/Enemy.h"
#include "EnemyHikers/LeftToRightHiker.h"
#include "EnemyHikers/StaticHiker.h"
#include "Finish.h"
#include "MainCharacter.h"
#include "PowerUps/InvincibilityStar.h"
#include "PowerUps/LaserBeam.h"
#include "PowerUps/Nuke.h"
#include "PowerUps/PowerUp.h"
#include "PowerUps/SpeedUp.h"
#include "PowerUps/SummonEnemy.h"

#include "SimpleAI.h"
#include <set>
#include <vector>

namespace TH {
class EntityMaker
{
public:
        /**
         * Generates the main character
         * @param lanes: used to calculate the initial position of the main character
         * @return a pointer to the main character
         */
        std::shared_ptr<MainCharacter> generateMainCharacter(int lanes);

        /**
         * Generates the finish line
         * @return a pointer to the finish line
         */
        std::shared_ptr<Finish> generateFinishLine();

        /**
         * Generates a simple AI
         * @return
         */
        static std::shared_ptr<SimpleAI> generateAI();

        /**
         * Generates a vector of pointer of enemies at random lanes with random offsets within the lane
         * @return A vector of enemies
         */
        static std::vector<std::shared_ptr<Enemy>> generateEnemies();

        /**
         * Generates a vector of pointer of power ups at random lanes with random offsets within the lane
         * @return A vector of power ups
         */
        std::vector<std::shared_ptr<PowerUp>> generatePowerUp();

        /**
         * Generate a random power up at a random offset
         * @param randomOffset: lane in which the power up will spawn
         * @return a random power up at a random offset
         */
        std::shared_ptr<PowerUp> generateRandomPowerUp(const float& randomOffset);

        /**
         * Generates three background entities
         * @return a vector of background entities
         */
        static std::vector<std::shared_ptr<Background>> generateBackground();

        /**
         * Summons a static hiker behind the main character
         */

        std::shared_ptr<Enemy> summonEnemy(const Position& pos);
};
} // namespace TH

#endif // TURBOHIKER_ENTITYMAKER_H
