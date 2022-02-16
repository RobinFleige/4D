#include "SpaceVector.h"
SpaceVector::SpaceVector(std::vector<double> values) {
    values_ = values;
}

std::vector<double> *SpaceVector::GetValues() {
    return &values_;
}
