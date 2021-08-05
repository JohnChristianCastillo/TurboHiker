//
// Created by JOHN CHRISTIAN CASTILLO on 7/18/2021.
//

#ifndef TURBOHIKER_MAINCHARACTER_H
#define TURBOHIKER_MAINCHARACTER_H

#include "Entity.h"
#include <vector>

class MainCharacter: public Entity {
    bool yelling{false};
    bool scareEnemy{false};

public:
    bool isScaringEnemy() const;
    void setScareEnemy(bool scareEnemy);

public:
    bool isYelling() const;
    void setYelling(bool yelling);

    /**
     * in a (-4,4) (-3,3) coordinate system. Our character needs to be placed at the lowest-middle
     * part of the screen
     * screen:
     *              6
     *       _______________
     *      |              |
     *      |              |
     *      |              |
     *    8 |              |
     *      |              |
     *      |              |
     *      |_____char_____|
     */

public:
     MainCharacter(int lanes);
     EntityTypes getType() const override{
         return EntityTypes::mainCharacter;
     }

     /**
      *
      * @return the area around the main character affected by it's yell/honk
      */
     std::vector<std::shared_ptr<GlobalBounds>> getAura(){
         Position mcPos = globalBounds->position;
         Dimentions mcDim = globalBounds->dimentions;
         std::shared_ptr<GlobalBounds> frontalAura1 = std::make_shared<GlobalBounds>(Position(mcPos.x, mcPos.y-mcDim.height), Dimentions(mcDim));
         std::shared_ptr<GlobalBounds> frontalAura2 = std::make_shared<GlobalBounds>(Position(mcPos.x, mcPos.y-2*mcDim.height), Dimentions(mcDim));
         std::shared_ptr<GlobalBounds> frontalAura3 = std::make_shared<GlobalBounds>(Position(mcPos.x, mcPos.y-3*mcDim.height), Dimentions(mcDim));
         std::shared_ptr<GlobalBounds> frontalAura4 = std::make_shared<GlobalBounds>(Position(mcPos.x, mcPos.y-4*mcDim.height), Dimentions(mcDim));
         std::shared_ptr<GlobalBounds> frontalLeftAura1 = std::make_shared<GlobalBounds>(Position(mcPos.x-mcDim.width, mcPos.y-mcDim.height), Dimentions(mcDim));
         std::shared_ptr<GlobalBounds> frontalLeftAura2 = std::make_shared<GlobalBounds>(Position(mcPos.x-mcDim.width, mcPos.y-2*mcDim.height), Dimentions(mcDim));
         std::shared_ptr<GlobalBounds> frontalLeftAura3 = std::make_shared<GlobalBounds>(Position(mcPos.x-mcDim.width, mcPos.y-3*mcDim.height), Dimentions(mcDim));
         std::shared_ptr<GlobalBounds> frontalLeftAura4 = std::make_shared<GlobalBounds>(Position(mcPos.x-mcDim.width, mcPos.y-4*mcDim.height), Dimentions(mcDim));
         std::shared_ptr<GlobalBounds> frontalRightAura1 = std::make_shared<GlobalBounds>(Position(mcPos.x+mcDim.width, mcPos.y-mcDim.height), Dimentions(mcDim));
         std::shared_ptr<GlobalBounds> frontalRightAura2 = std::make_shared<GlobalBounds>(Position(mcPos.x+mcDim.width, mcPos.y-2*mcDim.height), Dimentions(mcDim));
         std::shared_ptr<GlobalBounds> frontalRightAura3 = std::make_shared<GlobalBounds>(Position(mcPos.x+mcDim.width, mcPos.y-3*mcDim.height), Dimentions(mcDim));
         std::shared_ptr<GlobalBounds> frontalRightAura4 = std::make_shared<GlobalBounds>(Position(mcPos.x+mcDim.width, mcPos.y-4*mcDim.height), Dimentions(mcDim));

         std::shared_ptr<GlobalBounds> leftAura = std::make_shared<GlobalBounds>(Position(mcPos.x-mcDim.width, mcPos.y), Dimentions(mcDim));
         std::shared_ptr<GlobalBounds> rightAura = std::make_shared<GlobalBounds>(Position(mcPos.x+mcDim.width, mcPos.y), Dimentions(mcDim));
         return {frontalAura1, frontalAura2, frontalAura3, frontalAura4,
                 leftAura, rightAura,
                 frontalLeftAura1, frontalLeftAura2, frontalLeftAura3, frontalLeftAura4,
                 frontalRightAura1, frontalRightAura2, frontalRightAura3, frontalRightAura4};
     }


};


#endif//TURBOHIKER_MAINCHARACTER_H
