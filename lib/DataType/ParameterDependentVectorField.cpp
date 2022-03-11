#include <utility>
#include <valarray>
#include <iostream>
#include "ParameterDependentVectorField.h"

std::vector<std::vector<VectorField*>>& ParameterDependentVectorField::GetData() {
    return values_;
}

VectorField* ParameterDependentVectorField::GetVectorField(std::vector<int> ids) {
    return values_[ids[0]][ids[1]];
}

Vector ParameterDependentVectorField::GetData(std::vector<int> ids) {
    return values_[ids[0]][ids[1]]->GetData({ids[2],ids[3]});
}

ParameterDependentVectorField::ParameterDependentVectorField(int size) {
    size_ = size;
}

void ParameterDependentVectorField::SetData(std::vector<std::vector<VectorField*>> values) {
    values_ = std::move(values);
}

int ParameterDependentVectorField::GetSize() {
    return size_;
}

Vector ParameterDependentVectorField::GetInterpolated(std::vector<double> ids) {
    int points_count = pow(2,4);
    std::vector<double> factors;
    factors.reserve(points_count);
    std::vector<std::vector<int>> id_set;
    id_set.reserve(points_count);

    for(int i = 0; i < points_count; i++){
        double factor = 1;
        std::vector<int> rounded_ids;
        rounded_ids.reserve(4);

        for(int j = 0; j < 4; j++){
            if(i%((int)pow(2,j+1)) < (int)pow(2,j)){
                factor*=(floor(ids[j])-ids[j]+1);
                rounded_ids.push_back(floor(ids[j]));
            }else{
                factor*=(ids[j]-floor(ids[j]));
                rounded_ids.push_back(ceil(ids[j]));
            }
        }

        factors.push_back(factor);
        id_set.push_back(rounded_ids);
    }

    std::vector<double> values;
    values.reserve(2);
    for(int i = 0; i < 2; i++){
        values.push_back(0);
    }

    for(int i = 0; i < points_count; i++){
        for(int d = 0; d < 2; d++){
            values[d]+=factors[i]*GetData(id_set[i]).values_[d];
        }
    }

    auto vec = new Vector();
    vec->values_ = values;

    return *vec;
}

void ParameterDependentVectorField::SetFeatureFlowField(std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<double>>>>>> fff) {
    fff_ = std::move(fff);
}

std::vector<double> ParameterDependentVectorField::GetFFF(int s, int t, int x, int y, int d) {
    return fff_[s][t][x][y][0];
}

std::vector<double> ParameterDependentVectorField::GetInterpolatedFFF(double s, double t, double x, double y, int d) {
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
    std::vector<double> values;
    values.reserve(3);
    for(int i = 0; i < 3; i++){
        values.push_back(0);
    }
    for(int i = 0; i < 16; i++){
        //std::cout<<sp[i]<<" "<<tp[i]<<" "<<xp[i]<<" "<<yp[i]<<std::endl;
        values[0]+= factors[i]*fff_[sp[i]][tp[i]][xp[i]][yp[i]][d][0];
        values[1]+= factors[i]*fff_[sp[i]][tp[i]][xp[i]][yp[i]][d][1];
        values[2]+= factors[i]*fff_[sp[i]][tp[i]][xp[i]][yp[i]][d][2];
    }
    return values;
}
