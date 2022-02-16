#pragma once

#include <vector>
#include "FeatureFlowField.h"

class Point {
protected:
    std::vector<double> coordinates_;//per dimension
    std::vector<FeatureFlowField> fff_;//per parameter-dimension

public:
    std::vector<double> GetCoordinates();
    Point(std::vector<double> coordinates);
};