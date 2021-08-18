//
// Created by JOHN CHRISTIAN CASTILLO on 7/18/2021.
//

#include "EntityMaker.h"
std::shared_ptr<TH::MainCharacter> TH::EntityMaker::generateMainCharacter(int lanes)
{
        return std::make_shared<MainCharacter>(MainCharacter{lanes});
}
std::shared_ptr<TH::Finish> TH::EntityMaker::generateFinishLine() { return std::make_shared<Finish>(); }
std::vector<std::shared_ptr<TH::SimpleAI>> TH::EntityMaker::generateAI()
{
        return {std::make_shared<SimpleAI>(1), std::make_shared<SimpleAI>(2), std::make_shared<SimpleAI>(0.5)};
}
std::vector<std::shared_ptr<TH::Enemy>> TH::EntityMaker::generateEnemies()
{
        // assigns to which lane the enemy will go to:
        std::shared_ptr<singleton::Random> random = singleton::Random::getInstance();
        std::vector<std::shared_ptr<Enemy>> returnEnemies{};

        // generate left to right hikers
        int leftToRightHikersToGenerate = random->intInInterval(0, 2);
        for (int i = 0; i < leftToRightHikersToGenerate; ++i) {
                std::shared_ptr<Enemy> tempEnemy = std::make_shared<TH::LeftToRightHiker>(static_cast<float>(i));
                returnEnemies.push_back(tempEnemy);
        }
        // generate static hikers
        int staticHikersToGenerate = random->intInInterval(0, 2);
        std::set<int> set;
        while (set.size() != staticHikersToGenerate) {
                int randomOffset = random->intInInterval(0, 6);
                set.insert(randomOffset);
        }
        for (auto randomOffset : set) {
                float randomOffsetOffset = random->floatInInterval(-0.2, 0.2);
                std::shared_ptr<Enemy> tempEnemy =
                    std::make_shared<StaticHiker>(static_cast<float>(randomOffset) + randomOffsetOffset);
                float tempPosX = tempEnemy->getGlobalBounds()->position.x;
                float tempWidth = tempEnemy->getGlobalBounds()->dimensions.width;
                if (tempPosX + tempWidth / 2 >= 6 or tempPosX - tempWidth / 2 <= 0) {
                        tempEnemy = std::make_shared<StaticHiker>(static_cast<float>(randomOffset));
                }
                returnEnemies.push_back(tempEnemy);
        }
        return returnEnemies;
}
std::vector<std::shared_ptr<TH::PowerUp>> TH::EntityMaker::generatePowerUp()
{
        // assigns to which lane the enemy will go to:
        std::shared_ptr<singleton::Random> random = singleton::Random::getInstance();
        int powerUpsToGenerate = random->intInInterval(0, 1);
        std::vector<std::shared_ptr<PowerUp>> returnPowerUp{};
        std::set<int> set;
        while (set.size() != powerUpsToGenerate) {
                int randomOffset = random->intInInterval(0, 6);
                set.insert(randomOffset);
        }
        returnPowerUp.reserve(set.size());
        for (auto randomOffset : set) {
                returnPowerUp.push_back(generateRandomPowerUp(static_cast<float>(randomOffset)));
        }
        return returnPowerUp;
}
std::shared_ptr<TH::PowerUp> TH::EntityMaker::generateRandomPowerUp(const float& randomOffset)
{
        std::shared_ptr<singleton::Random> random = singleton::Random::getInstance();
        int powerUpIndex = random->intInInterval(0, 4);
        float randomOffsetOffset = random->floatInInterval(-0.2, 0.2);
        std::shared_ptr<PowerUp> powerUp{};
        float tempPosX;
        float tempWidth;
        switch (powerUpIndex) {
        case 0:
                powerUp = std::make_shared<SpeedUp>(static_cast<float>(randomOffset) + randomOffsetOffset);
                tempPosX = powerUp->getGlobalBounds()->position.x;
                tempWidth = powerUp->getGlobalBounds()->dimensions.width;
                if (tempPosX + tempWidth / 2 >= 6 or tempPosX - tempWidth / 2 <= 0) {
                        powerUp = std::make_shared<SpeedUp>(static_cast<float>(randomOffset));
                }
                break;
        case 1:
                powerUp = std::make_shared<InvincibilityStar>(static_cast<float>(randomOffset) + randomOffsetOffset);
                tempPosX = powerUp->getGlobalBounds()->position.x;
                tempWidth = powerUp->getGlobalBounds()->dimensions.width;
                if (tempPosX + tempWidth / 2 >= 6 or tempPosX - tempWidth / 2 <= 0) {
                        powerUp = std::make_shared<InvincibilityStar>(static_cast<float>(randomOffset));
                }
                break;
        case 2:
                powerUp = std::make_shared<SummonEnemy>(static_cast<float>(randomOffset) + randomOffsetOffset);
                tempPosX = powerUp->getGlobalBounds()->position.x;
                tempWidth = powerUp->getGlobalBounds()->dimensions.width;
                if (tempPosX + tempWidth / 2 >= 6 or tempPosX - tempWidth / 2 <= 0) {
                        powerUp = std::make_shared<SummonEnemy>(static_cast<float>(randomOffset));
                }
                break;
        case 3:
                powerUp = std::make_shared<Nuke>(static_cast<float>(randomOffset) + randomOffsetOffset);
                tempPosX = powerUp->getGlobalBounds()->position.x;
                tempWidth = powerUp->getGlobalBounds()->dimensions.width;
                if (tempPosX + tempWidth / 2 >= 6 or tempPosX - tempWidth / 2 <= 0) {
                        powerUp = std::make_shared<Nuke>(static_cast<float>(randomOffset));
                }
                break;
        case 4:
                powerUp = std::make_shared<LaserBeam>(static_cast<float>(randomOffset) + randomOffsetOffset);
                tempPosX = powerUp->getGlobalBounds()->position.x;
                tempWidth = powerUp->getGlobalBounds()->dimensions.width;
                if (tempPosX + tempWidth / 2 >= 6 or tempPosX - tempWidth / 2 <= 0) {
                        powerUp = std::make_shared<LaserBeam>(static_cast<float>(randomOffset));
                }
                break;

        default:
                break;
        }
        return powerUp;
}
std::vector<std::shared_ptr<TH::Background>> TH::EntityMaker::generateBackground()
{
        return {std::make_shared<Background>(0), std::make_shared<Background>(-1), std::make_shared<Background>(-2)};
}
std::shared_ptr<TH::Enemy> TH::EntityMaker::summonEnemy(const TH::Position& pos)
{
        return std::make_shared<StaticHiker>(pos);
}
