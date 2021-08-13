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
void Model::setPlayerMove(const Move &move) {
    Model::playerMove = move;
}
const Move &Model::getBackgroundMove() const {
    return backgroundMove;
}
void Model::setBackgroundMove(const Move &move) {
    Model::backgroundMove = move;
}
const std::shared_ptr<LiveScoring> &Model::getScoringSystem() const {
    return scoringSystem;
}
void Model::setSimpleAIMove(const Move &move) {
    Model::simpleAiMove = move;
}
const Move &Model::getSimpleAiMove() const {
    return simpleAiMove;
}
