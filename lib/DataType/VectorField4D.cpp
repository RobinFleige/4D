#include <valarray>
#include <iostream>
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

std::vector<double> VectorField4D::GetInterpolatedSpace(double s, double t, double x, double y) {
    std::vector<double> factor;
    factor.push_back((floor(x)-x+1)*(floor(y)-y+1));
    factor.push_back((x-floor(x))*(floor(y)-y+1));
    factor.push_back((floor(x)-x+1)*(y-floor(y)));
    factor.push_back((x-floor(x))*(y-floor(y)));

    std::vector<double> value;
    value.push_back(factor[0] * values_[(int)s][(int)t][floor(x)][floor(y)][0] + factor[1] * values_[(int)s][(int)t][ceil(x)][floor(y)][0]+factor[2] * values_[(int)s][(int)t][floor(x)][ceil(y)][0]+factor[3]*values_[(int)s][(int)t][ceil(x)][ceil(y)][0]);
    value.push_back(factor[0] * values_[(int)s][(int)t][floor(x)][floor(y)][1] + factor[1] * values_[(int)s][(int)t][ceil(x)][floor(y)][1]+factor[2] * values_[(int)s][(int)t][floor(x)][ceil(y)][1]+factor[3]*values_[(int)s][(int)t][ceil(x)][ceil(y)][1]);
    return value;
}

std::vector<double> VectorField4D::GetInterpolatedParameter(double s, double t, double x, double y) {
    std::vector<double> factors;
    for(int si = 0; si < 2; si++){
        for(int ti = 0; ti < 2; ti++){
            for(int xi = 0; xi < 2; xi++){
                for(int yi = 0; yi < 2; yi++){
                    double factor = 1;
                    if(si == 0){
                        factor = factor * (floor(s)-s+1);
                    }else{
                        factor = factor * (s-floor(s));
                    }
                    if(ti == 0){
                        factor = factor * (floor(t)-t+1);
                    }else{
                        factor = factor * (t-floor(t));
                    }
                    if(xi == 0){
                        factor = factor * (floor(x)-x+1);
                    }else{
                        factor = factor * (x-floor(x));
                    }
                    if(yi == 0){
                        factor = factor * (floor(y)-y+1);
                    }else{
                        factor = factor * (y-floor(y));
                    }
                    factors.push_back(factor);
                }
            }
        }
    }
    std::vector<int> sp;
    std::vector<int> tp;
    std::vector<int> yp;
    std::vector<int> xp;
    for(int si = 0; si < 2; si++){
        for(int ti = 0; ti < 2; ti++){
            for(int xi = 0; xi < 2; xi++){
                for(int yi = 0; yi < 2; yi++){
                    if(si == 0){
                        sp.push_back(floor(s));
                    }else{
                        sp.push_back(ceil(s));
                    }
                    if(ti == 0){
                        tp.push_back(floor(t));
                    }else{
                        tp.push_back(ceil(t));
                    }
                    if(xi == 0){
                        xp.push_back(floor(x));
                    }else{
                        xp.push_back(ceil(x));
                    }
                    if(yi == 0){
                        yp.push_back(floor(y));
                    }else{
                        yp.push_back(ceil(y));
                    }
                }
            }
        }
    }
    double value1 = 0;
    double value2 = 0;
    for(int i = 0; i < 16; i++){
        //std::cout<<sp[i]<<" "<<tp[i]<<" "<<xp[i]<<" "<<yp[i]<<std::endl;
        value1+= factors[i]*values_[sp[i]][tp[i]][xp[i]][yp[i]][0];
        value2+= factors[i]*values_[sp[i]][tp[i]][xp[i]][yp[i]][1];
    }
    std::vector<double> value;
    value.push_back(value1);
    value.push_back(value2);
    return value;
}