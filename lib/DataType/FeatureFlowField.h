#pragma once

#include <vector>

class FeatureFlowField {
    std::vector<double> value_;//per space-dimension +1
public:
    FeatureFlowField(std::vector<double> value);
    std::vector<double> GetValue();
};