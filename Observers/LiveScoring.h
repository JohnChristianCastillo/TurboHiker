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
        void saveHighScore() const;
        int position{1};

public:
        float getScore() const;

        /**
         * adds score after deleting an enemy via laser beam
         */
        void laseredEnemy();

        /**
         * deducts points for crashing into an enemy
         */
        void crashed();

        /**
         * By scaring a hiker too much, we can cause them to fall off
         */
        void hikerThrownOff();

        /**
         * Yelling can cause an enemy hiker to slow down
         */
        void hikerOffended();

        /**
         * Adds default score for advancing the race
         */
        void advance();

        /**
         * Returns the high score
         * Overwrites previous high score if new one is higher
         * @return the old/new high score
         */
        float getHighScore();

        /**
         * Rewards the player for finishing at a given position
         * @param position: The position the player finished on
         */
        void playerFinished(const int& position);

        /**
         * @return The position of the player
         */
        std::string getPosition() const;
};
} // namespace OBSERVER
} // namespace TH

#endif // TURBOHIKER_LIVESCORING_H
