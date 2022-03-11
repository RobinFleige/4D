#pragma once

#include "VectorField.h"

class ParameterDependentVectorField {
private:
    int size_;
    std::vector<std::vector<VectorField*>>  values_;
    std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<double>>>>>> fff_;
    //s,t,x,y,Parameterrichtung,fff
public:
    explicit ParameterDependentVectorField(int size);
    void SetData(std::vector<std::vector<VectorField*>>  values);
    std::vector<std::vector<VectorField*>>&  GetData();
    VectorField* GetVectorField(std::vector<int> ids);
    Vector GetData(std::vector<int> ids);
    int GetSize();
    Vector GetInterpolated(std::vector<double> ids);
    void SetFeatureFlowField(std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<double>>>>>> fff);
    std::vector<double> GetFFF(int s, int t, int x, int y, int d);
    std::vector<double> GetInterpolatedFFF(double s, double t, double x, double y, int d);
};
