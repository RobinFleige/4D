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
    VectorField* GetData(int s, int t);
    std::vector<double>& GetData(int s, int t, int x, int y);
    int GetSize();
    std::vector<double> GetInterpolated(double s, double t, double x, double y);
    void SetFeatureFlowField(std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<double>>>>>> fff);
    double GetFFF3(int s, int t, int x, int y);
    double GetInterpolatedFFF3(int s, int t, int x, int y);
};
