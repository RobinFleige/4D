#include "CriticalPoint.h"

CriticalPoint::CriticalPoint(std::vector<double> coordinates) : Point(coordinates) {
}

void CriticalPoint::AddFFF(std::vector<double> fff) {
    fff_.push_back(fff);
}

