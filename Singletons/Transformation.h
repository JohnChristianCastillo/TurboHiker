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
        Dimensions screenDimensions;
        explicit Transformation(Dimensions dimensions);

public:
        /**
         * @return The unique instance of transformation object
         */
        static std::shared_ptr<Transformation> getInstance();

        /**
         * Initialized the Transformation object
         * @param dimensions: the screen dimensions
         * @return The instance of Transformation
         */
        static std::shared_ptr<Transformation> init(Dimensions dimensions);

        /**
         * @return The dimensions of the screen
         */
        const Dimensions& getScreenDimensions();

        /**
         * converts the model's (0,6) (0,8) coordinate system into the
         * View's (0, screenWidth) (0, screenHeight) coordinate system
         * @param globalBounds
         * @return the center of the global bounds converted to the view coordinates
         */
        std::tuple<float, float> modelToView(const std::shared_ptr<GlobalBounds>& globalBounds) const;

        /**
         * Converts a dimension from model coordinate system to view coordinate system
         * @param modelDim
         * @return
         */
        Dimensions modelDimToViewDim(const Dimensions& modelDim) const;
};
} // namespace singleton
} // namespace TH
#endif // TURBOHIKER_TRANSFORMATION_H
