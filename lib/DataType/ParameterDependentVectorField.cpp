#include <utility>
#include <valarray>
#include <iostream>
#include "ParameterDependentVectorField.h"

std::vector<std::vector<VectorField*>>& ParameterDependentVectorField::GetData() {
    return values_;
}

VectorField* ParameterDependentVectorField::GetData(int s, int t) {
    return values_[s][t];
}

std::vector<double>& ParameterDependentVectorField::GetData(int s, int t, int x, int y) {
    return values_[s][t]->GetData(x,y);
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



std::vector<double> ParameterDependentVectorField::GetInterpolated(double s, double t, double x, double y) {
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
        value1+= factors[i]*values_[sp[i]][tp[i]]->GetData(xp[i],yp[i])[0];
        value2+= factors[i]*values_[sp[i]][tp[i]]->GetData(xp[i],yp[i])[1];
    }
    std::vector<double> value;
    value.push_back(value1);
    value.push_back(value2);
    return value;
}

void ParameterDependentVectorField::SetFeatureFlowField(std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<double>>>>>> fff) {
    fff_ = std::move(fff);
}

double ParameterDependentVectorField::GetFFF3(int s, int t, int x, int y) {
    return fff_[s][t][x][y][0][2];
}

double ParameterDependentVectorField::GetInterpolatedFFF3(int s, int t, int x, int y) {
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
    double value = 0;
    for(int i = 0; i < 16; i++){
        //std::cout<<sp[i]<<" "<<tp[i]<<" "<<xp[i]<<" "<<yp[i]<<std::endl;
        value+= factors[i]*fff_[sp[i]][tp[i]][xp[i]][yp[i]][0][2];
    }
    return value;
}
