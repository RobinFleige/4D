#pragma once

#include <vector>
#include "FeatureFlowField.h"
#include "CriticalPoint.h"

class BifurcationPoint : public CriticalPoint{
    std::vector<FeatureFlowField> meta_fff_;//per parameter-dimension -1
    std::vector<BifurcationPoint> previous_bifurcation_point_;//per parameter-dimension -1
    std::vector<BifurcationPoint> next_bifurcation_point_;//per parameter-dimension -1

};