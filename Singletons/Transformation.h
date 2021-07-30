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

    Dimentions screenDimentions;

    explicit Transformation(Dimentions dimentions);
    Transformation() = default;
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

    std::tuple<float, float> modelToView(const std::shared_ptr<Coordinates>& coords) const
    {
        //formula: newCoord = (x-csOrigMin)/(csOrigMax-csOrigMin) * (csDestMax-csDestMin) + csDestMin
        // calculating translated X
        //
        float newX = (coords->lowLeft.first/6)*screenDimentions.width;
        float newY = (coords->upRight.second/8)*screenDimentions.height;
        return std::make_tuple(newX, newY);
    }

    std::tuple<float, float> viewToModel(float x, float y) const
    {
        //formula: newCoord = (x-csOrigMin)/(csOrigMax-csOrigMin) * (csDestMax-csDestMin) + csDestMin
        // calculating translated X
        //
        float newX = (x/screenDimentions.width)*6;
        float newY = (y/screenDimentions.height)*8;
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
}//singleton
#endif // TURBOHIKER_TRANSFORMATION_H
