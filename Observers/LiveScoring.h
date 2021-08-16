//
// Created by reed on 03.08.21.
//

#ifndef TURBOHIKER_LIVESCORING_H
#define TURBOHIKER_LIVESCORING_H
#include <ostream>
#include <fstream>

namespace TH {
namespace OBSERVER {
class LiveScoring
{
        float score;
        void saveHighScore()
        {
                std::ofstream writeFile("../assets/Highscore.txt");
                if (writeFile.is_open()) {
                        writeFile << score;
                }
        }

public:
        float getScore() const;

        void crashed() { score -= 5; }
        /**
         * By scaring a hiker too much, we can cause them to fall off
         */
        void hikerThrownOff() { score -= 3; }
        /**
         * Yelling can cause an enemy hiker to slow down
         */
        void hikerOffended() { score -= 1; }

        void addPoints() { score += 10; }

        /**
         * Adds default score for advancing the race
         */
        void advance() { score += 0.06; }

        float getHighScore()
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
};
} // namespace OBSERVER
} // namespace TH

#endif // TURBOHIKER_LIVESCORING_H
