//
// Created by JOHN CHRISTIAN CASTILLO on 7/18/2021.
//

#include "Model.h"

namespace TH {
float Model::getFps() const { return fps; }
const Move& Model::getPlayerMove() const { return playerMove; }
void Model::setPlayerMove(const Move& move) { Model::playerMove = move; }
const Move& Model::getBackgroundMove() const { return backgroundMove; }
void Model::setBackgroundMove(const Move& move) { Model::backgroundMove = move; }
const std::shared_ptr<OBSERVER::LiveScoring>& Model::getScoringSystem() const { return scoringSystem; }
void Model::setSimpleAIMove(const Move& move) { Model::simpleAiMove = move; }
} // namespace TH
