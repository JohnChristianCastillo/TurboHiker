//
// Created by reed on 03.08.21.
//

#ifndef TURBOHIKER_LIVESCORING_H
#define TURBOHIKER_LIVESCORING_H


class LiveScoring {
    float score;
    int health;

public:
    void crashed(){
        score -= 5;
    }
    /**
     * By yelling loudly, our player can scare a hiker and cause them to panic
     */
    void scaredHiker(){
        score -=2;
    }
    /**
     * By scaring a hiker too much, we can cause them to fall off
     */
    void hikerThrownOff(){
        score -=3;
    }
    /**
     * Yelling can cause an enemy hiker to slow down
     */
    void hikerOffended(){
        score -= 1;
    }

    void addPoints(){
        score += 10;
    }
};


#endif//TURBOHIKER_LIVESCORING_H
