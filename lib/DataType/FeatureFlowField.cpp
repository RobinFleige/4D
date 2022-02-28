#include "FeatureFlowField.h"


FeatureFlowField::FeatureFlowField(std::vector<double> value) {
    value_ = value;
}

std::vector<double> FeatureFlowField::GetValue() {
    return value_;
}
