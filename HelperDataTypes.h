//
// Created by JOHN CHRISTIAN CASTILLO on 7/18/2021.
//

#ifndef TURBOHIKER_HELPERDATATYPES_H
#define TURBOHIKER_HELPERDATATYPES_H

#include <utility>
#include <memory>

/**
 * structure used to specify the coordinates of a given entity
 */
struct Coordinates
{
    std::pair<float, float> lowLeft;
    std::pair<float, float> upRight;

    Coordinates(std::pair<float, float> lowerLeft, std::pair<float, float> upperRight): lowLeft(lowerLeft), upRight(upperRight){}
};

enum EntityTypes
{
    mainCharacter,
    staticHiker
};

struct Dimentions{
    float width;
    float height;
};
#endif//TURBOHIKER_HELPERDATATYPES_H

