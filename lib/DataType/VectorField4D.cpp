#include <valarray>
#include "VectorField4D.h"

std::vector<std::vector<std::vector<std::vector<std::vector<double>>>>>& VectorField4D::GetData() {
    return values_;
}

std::vector<std::vector<std::vector<double>>>& VectorField4D::GetData(int s, int t) {
    return values_[s][t];
}

std::vector<double>& VectorField4D::GetData(int s, int t, int x, int y) {
    return values_[s][t][x][y];
}

VectorField4D::VectorField4D(int size) {
    size_ = size;
}

void VectorField4D::SetData(std::vector<std::vector<std::vector<std::vector<std::vector<double>>>>> values) {
    values_ = std::move(values);
}

int VectorField4D::GetSize() {
    return size_;
}

std::vector<double> VectorField4D::GetInterpolated(int s, int t, double x, double y) {
    std::vector<double> x_;
    std::vector<double> y_;
    if(floor(x)==ceil(x)){
        x_.push_back(floor(x));
        x_.push_back(floor(x));
    }else{
        x_.push_back(floor(x));
        x_.push_back(ceil(x));
    }
    if(floor(y)==ceil(y)){
        y_.push_back(floor(y));
        y_.push_back(floor(y));
    }else{
        y_.push_back(floor(y));
        y_.push_back(ceil(y));
    }

    std::vector<double> factor;
    factor.push_back((floor(x)-x+1)*(floor(y)-y+1));
    factor.push_back((x-floor(x))*(floor(y)-y+1));
    factor.push_back((floor(x)-x+1)*(y-floor(y)));
    factor.push_back((x-floor(x))*(y-floor(y)));

    std::vector<double> value;
    value.push_back(factor[0]*values_[s][t][x_[0]][y_[0]][0]+factor[1]*values_[s][t][x_[1]][y_[0]][0]+factor[2]*values_[s][t][x_[0]][y_[1]][0]+factor[3]*values_[s][t][x_[1]][y_[1]][0]);
    value.push_back(factor[0]*values_[s][t][x_[0]][y_[0]][1]+factor[1]*values_[s][t][x_[1]][y_[0]][1]+factor[2]*values_[s][t][x_[0]][y_[1]][1]+factor[3]*values_[s][t][x_[1]][y_[1]][1]);
    return value;
}
