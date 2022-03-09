#include "CriticalPoint.h"

CriticalPoint::CriticalPoint(std::vector<double> coordinates, CriticalPointType type) : Point(coordinates) {
    type_ = type;
}

void CriticalPoint::AddFFF(std::vector<double> fff) {
    fff_.push_back(fff);
}

CriticalPointType CriticalPoint::GetCriticalPointType() {
    return type_;
}

