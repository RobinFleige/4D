#include <valarray>
#include "VectorField.h"

std::vector<std::vector<std::vector<double>>>& VectorField::GetData() {
    return values_;
}

VectorField::VectorField(int size) {
    size_ = size;
}

void VectorField::SetData(std::vector<std::vector<std::vector<double>>> values) {
    values_ = std::move(values);
}

int VectorField::GetSize() {
    return size_;
}

std::vector<double>& VectorField::GetData(int x, int y) {
    return values_[x][y];
}

std::vector<double> VectorField::GetInterpolated(double x, double y) {
    std::vector<double> factor;
    factor.push_back((floor(x)-x+1)*(floor(y)-y+1));
    factor.push_back((x-floor(x))*(floor(y)-y+1));
    factor.push_back((floor(x)-x+1)*(y-floor(y)));
    factor.push_back((x-floor(x))*(y-floor(y)));

    std::vector<double> value;
    value.push_back(factor[0] * values_[floor(x)][floor(y)][0] + factor[1] * values_[ceil(x)][floor(y)][0]+factor[2] * values_[floor(x)][ceil(y)][0]+factor[3]*values_[ceil(x)][ceil(y)][0]);
    value.push_back(factor[0] * values_[floor(x)][floor(y)][1] + factor[1] * values_[ceil(x)][floor(y)][1]+factor[2] * values_[floor(x)][ceil(y)][1]+factor[3]*values_[ceil(x)][ceil(y)][1]);
    return value;
}