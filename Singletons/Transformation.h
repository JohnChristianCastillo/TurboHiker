//
// Created by JOHN CHRISTIAN CASTILLO on 12/27/2020.
//

#ifndef TURBOHIKER_TRANSFORMATION_H
#define TURBOHIKER_TRANSFORMATION_H

#include "../HelperDataTypes.h"
#include <iostream>
#include <memory>

namespace TH {
namespace singleton {
class Transformation
{
        static std::shared_ptr<Transformation> transformation;

        Dimentions screenDimentions;

        explicit Transformation(Dimentions dimentions);

public:
        static std::shared_ptr<Transformation> getInstance() { return transformation; }

        static std::shared_ptr<Transformation> init(Dimentions dimentions)
        {
                if (!transformation) {
                        transformation = std::make_shared<Transformation>(Transformation{dimentions});
                }
                return transformation;
        }

        const Dimentions& getScreenDimentions() { return screenDimentions; }
        /**
         * converts the model's (0,6) (0,8) coordinate system into the
         * View's (0, screenWidth) (0, screenHeight) coordinate system
         * @param coords
         * @param screenWidth
         * @param screenHeight
         * @return
         */

        /**
         *
         * @param globalBounds
         * @return the center of the global bounds converted to the view coordinates
         */
        std::tuple<float, float> modelToView(const std::shared_ptr<GlobalBounds>& globalBounds) const
        {
                // formula: newCoord = (x-csOrigMin)/(csOrigMax-csOrigMin) * (csDestMax-csDestMin) + csDestMin
                //  calculating translated X
                //
                float newX = (globalBounds->position.x / 6) * screenDimentions.width;
                float newY = (globalBounds->position.y / 8) * screenDimentions.height;
                return std::make_tuple(newX, newY);
        }

        Dimentions modelDimToViewDim(const Dimentions& modelDim) const
        {
                float width = (modelDim.width / 6) * screenDimentions.width;
                float height = (modelDim.height / 8) * screenDimentions.height;
                return {width, height};
        }
        std::tuple<float, float> viewToModel(float x, float y) const
        {
                // formula: newCoord = (x-csOrigMin)/(csOrigMax-csOrigMin) * (csDestMax-csDestMin) + csDestMin
                //  calculating translated X
                //
                float newX = (x / screenDimentions.width) * 6;
                float newY = (y / screenDimentions.height) * 8;

                return std::make_tuple(newX, newY);
        }

        /*std::shared_ptr<Coordinates> viewToModel(const std::shared_ptr<Coordinates>& coords, const float& screenWidth,
                                             const float& screenHeight)
    {
            float ratioX = screenWidth / 6;
            float ratioY = screenHeight / 6;
            std::shared_ptr<Coordinates> retVal{std::make_shared<Coordinates>()};
            retVal->upRight = std::make_pair(coords->upRight.first / ratioX, coords->upRight.second / ratioY);
            retVal->lowLeft = std::make_pair(coords->lowLeft.first / ratioX, coords->lowLeft.second / ratioY);

            return retVal;
    }*/
};
} // namespace singleton
} // namespace TH
#endif // TURBOHIKER_TRANSFORMATION_H
