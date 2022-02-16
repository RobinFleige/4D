#pragma once

#include <vector>
#include "FeatureFlowField.h"

class Point {
    std::vector<double> coordinates_;//per dimension
    std::vector<FeatureFlowField> fff_;//per parameter-dimension
};