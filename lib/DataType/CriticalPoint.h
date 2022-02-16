#pragma once

#include <vector>
#include "Point.h"

class CriticalPoint : Point {
    std::vector<CriticalPoint> previous_critical_point_;//per parameter-dimension
    std::vector<CriticalPoint> next_critical_point_;//per parameter-dimension

};