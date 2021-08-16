//
// Created by JOHN CHRISTIAN CASTILLO on 12/27/2020.
//

#include "Transformation.h"
std::shared_ptr<TH::singleton::Transformation> TH::singleton::Transformation::transformation = nullptr;
TH::singleton::Transformation::Transformation(Dimensions dimensions) : screenDimensions(dimensions) {}
std::shared_ptr<TH::singleton::Transformation> TH::singleton::Transformation::getInstance() { return transformation; }
std::shared_ptr<TH::singleton::Transformation> TH::singleton::Transformation::init(TH::Dimensions dimensions)
{
        if (!transformation) {
                transformation = std::make_shared<Transformation>(Transformation{dimensions});
        }
        return transformation;
}
const TH::Dimensions& TH::singleton::Transformation::getScreenDimensions() { return screenDimensions; }
std::tuple<float, float> TH::singleton::Transformation::modelToView(
    const std::shared_ptr<GlobalBounds>& globalBounds) const
{
        // formula: newCoord = (x-csOrigMin)/(csOrigMax-csOrigMin) * (csDestMax-csDestMin) + csDestMin
        //  calculating translated X
        //
        float newX = (globalBounds->position.x / 6) * screenDimensions.width;
        float newY = (globalBounds->position.y / 8) * screenDimensions.height;
        return std::make_tuple(newX, newY);
}
TH::Dimensions TH::singleton::Transformation::modelDimToViewDim(const TH::Dimensions& modelDim) const
{
        float width = (modelDim.width / 6) * screenDimensions.width;
        float height = (modelDim.height / 8) * screenDimensions.height;
        return {width, height};
}
