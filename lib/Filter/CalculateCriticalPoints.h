#pragma once
#include <vector>
#include <vtkImageData.h>
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include "../PipelineDefs/Filter.h"
#include "../DataType/CriticalPoint.h"
#include "../DataType/ParameterDependentVectorField.h"

class CalculateCriticalPoints : public Filter<ParameterDependentVectorField*,ParameterDependentVectorField*> {
private:
    int subdivision_depth_;

    std::vector<CriticalPoint*> Subdivide(bool interpolate, int max_iterations, std::vector<std::vector<double>> ids);
    void InternalUpdate() override;
public:
    CalculateCriticalPoints(int subdivision_depth);
};