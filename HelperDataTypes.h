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
 /*
struct Coordinates
{
    //          x      y
    std::pair<float, float> lowLeft;
    std::pair<float, float> upRight;

    Coordinates(std::pair<float, float> lowerLeft, std::pair<float, float> upperRight): lowLeft(lowerLeft), upRight(upperRight){}
};
*/
struct Position{
    float x;
    float y;
    Position(float xCor, float yCor):x(xCor), y(yCor){}
    Position(const Position& pos) = default;
};

enum EntityTypes
{
    mainCharacter,
    staticHiker,
    background
};


struct Dimentions{
    float width;
    float height;
    Dimentions(float _width, float _height):width(_width), height(_height){};
    Dimentions(const Dimentions& dim) = default;
};

struct Move{
    float x;
    float y;
};

enum Input{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    ZERO,
    ONE
};
struct GlobalBounds{
    Position position;
    Dimentions dimentions;

    GlobalBounds(const Position& pos, const Dimentions& dim): position(pos), dimentions(dim) {};
};
#endif//TURBOHIKER_HELPERDATATYPES_H

