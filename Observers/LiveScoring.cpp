//
// Created by reed on 03.08.21.
//

#include "LiveScoring.h"
float TH::OBSERVER::LiveScoring::getScore() const { return score; }
void TH::OBSERVER::LiveScoring::saveHighScore() const
{
        std::ofstream writeFile("../assets/Highscore.txt");
        if (writeFile.is_open()) {
                writeFile << score;
        }
}
void TH::OBSERVER::LiveScoring::laseredEnemy() { score += 100; }
void TH::OBSERVER::LiveScoring::crashed() { score -= 500; }
void TH::OBSERVER::LiveScoring::hikerThrownOff() { score -= 3 * 100; }
void TH::OBSERVER::LiveScoring::hikerOffended() { score -= 30; }
void TH::OBSERVER::LiveScoring::advance() { score += 0.06 * 1000; }
float TH::OBSERVER::LiveScoring::getHighScore()
{
        float highScore = 0;
        std::ifstream readFile;
        readFile.open("../assets/Highscore.txt");
        if (readFile.is_open()) {
                while (!readFile.eof()) {
                        readFile >> highScore;
                }
                if (score > highScore) {
                        highScore = score;
                        readFile.close();
                        saveHighScore();
                }
        }
        readFile.close();
        return highScore;
}
void TH::OBSERVER::LiveScoring::playerFinished(const int& _position)
{
        position = _position;
        score += (4.f - static_cast<float>(position)) * 2000;
}

std::string TH::OBSERVER::LiveScoring::getPosition() const
{
        if (position == 1) {
                return "1st";
        } else if (position == 2) {
                return "2nd";
        } else if (position == 3) {
                return "3rd";
        } else {
                return "4th";
        }
}
