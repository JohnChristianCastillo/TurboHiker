//
// Created by JOHN CHRISTIAN CASTILLO on 7/18/2021.
//

#include "StaticHiker.h"
StaticHiker::StaticHiker(const int &horizontalOffset) {
    coordinates = std::make_shared<Coordinates>(std::make_pair(0.f + float(horizontalOffset), 1.f),
                                                std::make_pair(1.f + float(horizontalOffset), 0.f));
}
