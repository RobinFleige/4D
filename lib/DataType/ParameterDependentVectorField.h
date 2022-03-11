#pragma once

#include "VectorField.h"

class ParameterDependentVectorField {
private:
    int parameter_dimensions_;
    int space_dimensions_;
    int size_;

    std::vector<VectorField*>  vector_fields;
    std::vector<VectorField*> fffs_;
    //Parameterrichtung,s,t,x,y,fff

    int IDFromIDs(std::vector<int> ids);
    std::vector<int> IDsFromID(int id);
public:
    explicit ParameterDependentVectorField(int parameter_dimensions, int space_dimensions, int size);

    void SetData(std::vector<VectorField*>  vector_fields);
    void SetFeatureFlowField(std::vector<VectorField*> fffs);

    VectorField* GetVectorField(std::vector<int> ids);
    Vector GetData(std::vector<int> ids);
    Vector GetInterpolated(std::vector<double> ids);
    Vector GetFFF(std::vector<int> ids, int d);
    Vector GetInterpolatedFFF(std::vector<double> ids, int d);

    int GetSize();
    int GetDimensions();
    int GetParameterDimensions();
    int GetSpaceDimensions();

    int IDFromIDsFull(std::vector<int> ids);
    std::vector<int> IDsFromIDFull(int id);

};
