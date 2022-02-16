#pragma once

#include "SpaceVector.h"

class VectorField {
private:
    int parameter_dimensions_;
    int space_dimensions_;
    int dimensions_;

    std::vector<int> lengths_;
    std::vector<SpaceVector*> vectors_;
public:
    VectorField(int parameter_dimensions, int space_dimensions, std::vector<int> lengths);
    void SetData(std::vector<SpaceVector*> vectors);
    std::vector<int> IDsFromID(int id);
    int IDFromIDs(std::vector<int> ids);
    std::vector<int> GetLengths();
    int GetParameterDimensions();
    int GetSpaceDimensions();
    int GetDimensions();
    std::vector<SpaceVector*> GetData();
    std::vector<double> GetInterpolated(std::vector<double> ids);
};