#include "CriticalPoint.h"

CriticalPoint::CriticalPoint(std::vector<double> coordinates, CriticalPointType type) : Point(coordinates) {
    type_ = type;
}

CriticalPointType CriticalPoint::GetCriticalPointType() {
    return type_;
}

