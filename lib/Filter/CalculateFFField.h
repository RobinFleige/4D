#pragma once
#include <vector>
#include <DataType/ParameterDependentVectorField.h>
#include "../PipelineDefs/Filter.h"
#include "DataType/Point.h"

class CalculateFFField : public Filter<ParameterDependentVectorField*,ParameterDependentVectorField*> {
private:
    void InternalUpdate() override;
    double Determinant(std::vector<std::vector<double>> matrix);
public:
    CalculateFFField();
};