//
// Created by JOHN CHRISTIAN CASTILLO on 7/18/2021.
//

#include "Model.h"

float Model::getFps() const {
    return fps;
}
const Move &Model::getPlayerMove() const {
    return playerMove;
}
void Model::setPlayerMoveX(const float &moveX) {
    Model::playerMove.x = moveX;
}
void Model::setPlayerMoveY(const float &moveY) {
    Model::playerMove.y = moveY;
}
const Move &Model::getBackgroundMove() const {
    return backgroundMove;
}
void Model::setBackgroundMoveY(const float &moveY) {
    Model::backgroundMove.y = moveY;
}
const std::shared_ptr<LiveScoring> &Model::getScoringSystem() const {
    return scoringSystem;
}
