//
// Created by JOHN CHRISTIAN CASTILLO on 7/18/2021.
//

#ifndef TURBOHIKER_MAINCHARACTER_H
#define TURBOHIKER_MAINCHARACTER_H

#include "Entity.h"

class MainCharacter: public Entity {

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
     MainCharacter();
     EntityTypes getType() const override{
         return EntityTypes::mainCharacter;
     }
     float getMovementSpeed() const override{
         return movementSpeed;
     }


};


#endif//TURBOHIKER_MAINCHARACTER_H
