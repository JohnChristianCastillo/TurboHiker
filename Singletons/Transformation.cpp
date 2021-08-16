//
// Created by JOHN CHRISTIAN CASTILLO on 12/27/2020.
//

#include "Transformation.h"
std::shared_ptr<TH::singleton::Transformation> TH::singleton::Transformation::transformation = nullptr;
TH::singleton::Transformation::Transformation(Dimentions dimentions) : screenDimentions(dimentions) {}