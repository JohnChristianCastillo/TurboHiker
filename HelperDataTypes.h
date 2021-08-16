//
// Created by JOHN CHRISTIAN CASTILLO on 7/18/2021.
//

#ifndef TURBOHIKER_HELPERDATATYPES_H
#define TURBOHIKER_HELPERDATATYPES_H

#include <utility>
#include <memory>

namespace TH {
/**
 * structure used to specify the coordinates of a given entity
 */
struct Position
{
        float x;
        float y;
        Position(float xCor, float yCor) : x(xCor), y(yCor) {}
        Position(const Position& pos) = default;
};

enum EntityTypes
{
        mainCharacter,
        staticHiker,
        leftToRightHiker,
        background,
        finishLine,
        speedUp,
        invincibilityStar
};

struct Dimentions
{
        float width;
        float height;
        Dimentions(float _width, float _height) : width(_width), height(_height){};
        Dimentions(const Dimentions& dim) = default;
};

struct Move
{
        float x;
        float y;
        Move(const float& _x, const float& _y) : x(_x), y(_y){};
        Move() = default;
        Move operator*(const float& movementSpeed)
        {
                x *= movementSpeed;
                y *= movementSpeed;
        }
};

enum Input
{
        UP,
        DOWN,
        LEFT,
        RIGHT,
        HONKING,
        SCARING,
        ZERO,
        ENTER
};
struct GlobalBounds
{
        Position position;
        Dimentions dimentions;

        GlobalBounds(const Position& pos, const Dimentions& dim) : position(pos), dimentions(dim){};
        /**
         * Keep in mind that we are working with rectangle objects
         * @param nextPosition
         * @return
         */
        template <typename type>
        bool intersects(const std::shared_ptr<GlobalBounds>& nextPosition) const
        {

                // calculate leftX and topY of current
                type left = position.x - dimentions.width / 2;
                type top = position.y - dimentions.height / 2;

                // calculate leftX and topY of other object
                type nextLeft = nextPosition->position.x - nextPosition->dimentions.width / 2;
                type nextTop = nextPosition->position.y - nextPosition->dimentions.height / 2;

                // Compute the min and max x and y of the the entity we're in

                type thisMinX = left;
                type thisMaxX = static_cast<type>(left + dimentions.width);
                type thisMinY = top;
                type thisMaxY = static_cast<type>(top + dimentions.height);

                // Compute the min and max x and y of the the next position we're in
                type r2MinX = nextLeft;
                type r2MaxX = static_cast<type>(nextLeft + dimentions.width);
                type r2MinY = nextTop;
                type r2MaxY = static_cast<type>(nextTop + dimentions.height);

                // Compute the intersection boundaries
                type interLeft = std::max(thisMinX, r2MinX);
                type interTop = std::max(thisMinY, r2MinY);
                type interRight = std::min(thisMaxX, r2MaxX);
                type interBottom = std::min(thisMaxY, r2MaxY);

                bool b = (interLeft < interRight) && (interTop < interBottom);
                return b;
        }
};
} // namespace TH
#endif // TURBOHIKER_HELPERDATATYPES_H
