//
// Created by JOHN CHRISTIAN CASTILLO on 7/18/2021.
//

#ifndef TURBOHIKER_HELPERDATATYPES_H
#define TURBOHIKER_HELPERDATATYPES_H

#include <utility>
#include <memory>

namespace TH {

/**
 * Possible game inputs
 */
enum Input
{
        UP,
        DOWN,
        LEFT,
        RIGHT,
        HONKING,
        SCARING,
        ZERO,
        ENTER,
        SPAWNENEMY
};

/**
 * The different entities in the Turbo hiker game
 */
enum EntityTypes
{
        mainCharacter,
        staticHiker,
        leftToRightHiker,
        background,
        finishLine,
        speedUp,
        invincibilityStar,
        summonEnemy,
        nukePowerUp,
        laserBeamPowerUp
};

/**
 * structure used to specify the coordinates of a given entity
 */
struct Position
{
        float x;
        float y;
        /**
         * Instantiates a Position object at coordinates (xCor, yCor)
         * @param xCor: the x coordinate we want to instantiate Position in
         * @param yCor: the y coordinate we want to instantiate Position in
         */
        Position(float xCor, float yCor) : x(xCor), y(yCor) {}

        /**
         * A copy constructor of Position
         * @param pos
         */
        Position(const Position& pos) = default;
};

struct Dimensions
{
        float width;
        float height;

        /**
         * Instantiate Dimensions with width = _width and height = _height
         * @param _width: The width we want our dimension to have
         * @param _height: Th height we want our dimension to have
         */
        Dimensions(float _width, float _height) : width(_width), height(_height){};

        /**
         * A copy constructor of Dimension
         * @param dim
         */
        Dimensions(const Dimensions& dim) = default;
};

struct Move
{
        float x;
        float y;

        /**
         * Instantiate Move with x = _x and y = _y
         * @param _x: Offset we want to use for the x coordinate
         * @param _y: Offset we want to use for the y cooridnate
         */
        Move(const float& _x, const float& _y) : x(_x), y(_y){};
        Move() = default;

        Move operator*(const float& movementSpeed)
        {
                x *= movementSpeed;
                y *= movementSpeed;
        }
};

struct GlobalBounds
{
        Position position;
        Dimensions dimensions;

        /**
         * Instantiates GlobalBounds at position = pos and dimension = dim
         * @param pos: Position we want to instantiate the GlobalBounds position
         * @param dim: Dimension we want to instantiate the GlobalBounds dimension
         */
        GlobalBounds(const Position& pos, const Dimensions& dim) : position(pos), dimensions(dim){};
        /**
         * Keep in mind that we are working with rectangle objects
         * @param nextPosition: The GlobalBounds of another entity
         * @return True if this instance of GlobalBounds intersects with the nextPosition
         */
        template <typename type>
        bool intersects(const std::shared_ptr<GlobalBounds>& nextPosition) const
        {

                // calculate leftX and topY of current
                type left = position.x - dimensions.width / 2;
                type top = position.y - dimensions.height / 2;

                // calculate leftX and topY of other object
                type nextLeft = nextPosition->position.x - nextPosition->dimensions.width / 2;
                type nextTop = nextPosition->position.y - nextPosition->dimensions.height / 2;

                // Compute the min and max x and y of the the entity we're in

                type thisMinX = left;
                type thisMaxX = static_cast<type>(left + dimensions.width);
                type thisMinY = top;
                type thisMaxY = static_cast<type>(top + dimensions.height);

                // Compute the min and max x and y of the the next position we're in
                type r2MinX = nextLeft;
                type r2MaxX = static_cast<type>(nextLeft + dimensions.width);
                type r2MinY = nextTop;
                type r2MaxY = static_cast<type>(nextTop + dimensions.height);

                // Compute the intersection boundaries
                type interLeft = std::max(thisMinX, r2MinX);
                type interTop = std::max(thisMinY, r2MinY);
                type interRight = std::min(thisMaxX, r2MaxX);
                type interBottom = std::min(thisMaxY, r2MaxY);

                return (interLeft < interRight) && (interTop < interBottom);
        }
};
} // namespace TH
#endif // TURBOHIKER_HELPERDATATYPES_H
