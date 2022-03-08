#pragma once
#include <vector>
#include "Point.h"

class CriticalPoint : public Point {
    std::vector<CriticalPoint*> previous_critical_point_;//per parameter-dimension
    std::vector<CriticalPoint*> next_critical_point_;//per parameter-dimension

public:
    CriticalPoint(std::vector<double> coordinates);

    void AddFFF(std::vector<double> fff);

};