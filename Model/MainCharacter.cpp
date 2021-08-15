//
// Created by JOHN CHRISTIAN CASTILLO on 7/18/2021.
//

#include "MainCharacter.h"
#include "../Singletons/Timer.h"
MainCharacter::MainCharacter(int lanes) {
    /// todo: 8 divided by lanes doesnt really make sense;
    Position pos = Position(6.f/static_cast<float>(lanes)*2, 5.5f);
    Dimentions dim = Dimentions(0.222222f, 0.444444f);
    globalBounds = std::make_shared<GlobalBounds>(pos, dim);
    movementSpeed = 5;
}
bool MainCharacter::isYelling() const {
    return yelling;
}
void MainCharacter::setYelling(bool yell) {
    MainCharacter::yelling = yell;
}
bool MainCharacter::isScaringEnemy(){
    return scareEnemy;
}
void MainCharacter::setScareEnemy(bool scareEnemy) {
    MainCharacter::scareEnemy = scareEnemy;
}
float MainCharacter::getScareCooldown() const {
    if(scareCooldown <0){
        return 0;
    }
    return scareCooldown;
}
void MainCharacter::resetScareCooldown() {
    MainCharacter::scareCooldown = 15;
}
void MainCharacter::setInvincible(bool invincible) {
    MainCharacter::invincible = invincible;
}
