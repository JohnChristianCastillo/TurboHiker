//
// Created by JOHN CHRISTIAN CASTILLO on 12/27/2020.
//

#ifndef TURBOHIKER_TRANSFORMATION_H
#define TURBOHIKER_TRANSFORMATION_H

#include "../HelperDataTypes.h"
#include <memory>

namespace singleton{
class Transformation
{
        static std::shared_ptr<Transformation> transformation;

        Dimentions screenDimentions{};

        Transformation(Dimentions dimentions):screenDimentions(dimentions){};
public:
        static std::shared_ptr<Transformation> getInstance()
        {
                return transformation;
        }


        static std::shared_ptr<Transformation> init(Dimentions dimentions){
                if(!transformation){
                        transformation = std::make_shared<Transformation>(Transformation{dimentions});
                }
                return transformation;
        }

        const Dimentions& getScreenDimentions(){
                return screenDimentions;
        }
        /**
         * converts the model's (0,6) (0,8) coordinate system into the
         * View's (0, screenWidth) (0, screenHeight) coordinate system
         * @param coords
         * @param screenWidth
         * @param screenHeight
         * @return
         */
        std::shared_ptr<Coordinates> modelToView(const std::shared_ptr<Coordinates>& coords)
        {
                float ratioX = screenDimentions.width/6;
                float ratioY = screenDimentions.height/8;
                std::shared_ptr<Coordinates> retVal{std::make_shared<Coordinates>(std::make_pair(coords->lowLeft.first * ratioX, coords->lowLeft.second * ratioY),
                                                                                  std::make_pair(coords->upRight.first * ratioX, coords->upRight.second * ratioY))};

                return retVal;
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
}//singleton
#endif // TURBOHIKER_TRANSFORMATION_H
