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
    //          x      y
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
    Dimentions(float _width, float _height):width(_width), height(_height){};
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
    float left;
    float top;
    Dimentions dimentions;
    GlobalBounds(float _left, float _top, Dimentions _dimentions):left(_left), top(_top), dimentions(_dimentions){

    }
    /**
     * Keep in mind that we are working with rectangle objects
     * @param nextPosition
     * @return
     */
    template<typename type>
    bool intersects(const std::shared_ptr<GlobalBounds>& nextPosition) const{
        // Compute the min and max x and y of the the entity we're in
        type thisMinX = std::min(left, static_cast<type>(left + dimentions.width));
        type thisMaxX = std::max(left, static_cast<type>(left + dimentions.width));
        type thisMinY = std::min(top, static_cast<type>(top + dimentions.height));
        type thisMaxY = std::min(top, static_cast<type>(top + dimentions.height));

        // Compute the min and max x and y of the the next position we're in
        type r2MinX = std::min(nextPosition->left, static_cast<type>(nextPosition->left + nextPosition->dimentions.width));
        type r2MaxX = std::max(nextPosition->left, static_cast<type>(nextPosition->left + nextPosition->dimentions.width));
        type r2MinY = std::min(nextPosition->top, static_cast<type>(nextPosition->top + nextPosition->dimentions.height));
        type r2MaxY = std::max(nextPosition->top, static_cast<type>(nextPosition->top + nextPosition->dimentions.height));

        // Compute the intersection boundaries
        type interLeft   = std::max(thisMinX, r2MinX);
        type interTop    = std::max(thisMinY, r2MinY);
        type interRight  = std::min(thisMaxX, r2MaxX);
        type interBottom = std::min(thisMaxY, r2MaxY);

        return (interLeft < interRight) && (interTop < interBottom);
    }
};
#endif//TURBOHIKER_HELPERDATATYPES_H

