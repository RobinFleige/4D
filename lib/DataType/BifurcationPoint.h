#pragma once

#include <vector>
#include "CriticalPoint.h"

class BifurcationPoint : public CriticalPoint{

    std::vector<std::vector<double>> meta_fff_;//per parameter-dimension -1
    std::vector<BifurcationPoint> previous_bifurcation_point_;//per parameter-dimension -1
    std::vector<BifurcationPoint> next_bifurcation_point_;//per parameter-dimension -1

public:
    explicit BifurcationPoint(std::vector<double> coordinates);

};