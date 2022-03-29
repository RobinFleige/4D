#pragma once

#include "VectorField.h"
#include "Point.h"
#include <utility>
#include <valarray>
#include <iostream>

class ParameterDependentVectorField {
private:
    int parameter_dimensions_;
    int space_dimensions_;
    int size_;

    std::vector<VectorField*>  vector_fields;
    std::vector<VectorField*> fffs_;
    std::vector<Point*> critical_points_;
    //Parameterrichtung,s,t,x,y,fff

public:
    explicit ParameterDependentVectorField(int parameter_dimensions, int space_dimensions, int size);

    void SetData(std::vector<VectorField*>  vector_fields);
    void SetFeatureFlowField(std::vector<VectorField*> fffs);

    VectorField* GetVectorField(std::vector<int> ids);
    Vector GetData(std::vector<int> ids);
    Vector GetInterpolated(std::vector<double> ids);
    Vector GetFFF(std::vector<int> ids, int d);
    Vector GetInterpolatedFFF(std::vector<double> ids, int d);

    void AppendCriticalPoints(std::vector<Point*> critical_points);
    std::vector<Point*> GetCriticalPoints();

    int GetSize();
    int GetDimensions();
    int GetParameterDimensions();
    int GetSpaceDimensions();

    int IDFromParameterIDs(std::vector<int> ids);
    std::vector<int> ParameterIDsFromID(int id);
    int IDFromSpaceIDs(std::vector<int> ids);
    std::vector<int> SpaceIDsFromID(int id);
    int IDFromIDs(std::vector<int> ids);
    std::vector<int> IDsFromID(int id);

};
