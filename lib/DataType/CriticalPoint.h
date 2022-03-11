#pragma once
#include <vector>
#include "Point.h"


enum CriticalPointType {sink = -1, saddle = 0, source = 1, bifurcation = 100};

class CriticalPoint : public Point {
    std::vector<CriticalPoint*> previous_critical_point_;//per parameter-dimension
    std::vector<CriticalPoint*> next_critical_point_;//per parameter-dimension
    CriticalPointType type_;

public:
    CriticalPoint(std::vector<double> coordinates,CriticalPointType type);
    CriticalPointType GetCriticalPointType();

};