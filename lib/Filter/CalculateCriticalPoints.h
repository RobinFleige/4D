#pragma once
#include <vector>
#include <vtkImageData.h>
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include "../PipelineDefs/Filter.h"
#include "../DataType/Point.h"
#include "../DataType/ParameterDependentVectorField.h"

class CalculateCriticalPoints : public Filter<ParameterDependentVectorField*,ParameterDependentVectorField*> {
private:
    int subdivision_depth_;

    std::vector<Point*> Subdivide(int max_iterations, std::vector<std::vector<double>> ids);
    void InternalUpdate() override;

    bool OnRightBorder(std::vector<int> ids);
    std::vector<std::vector<double>> CalculateMinMaxSet(std::vector<int> ids);
    std::vector<std::vector<double>> CalculateMinMaxCorners(std::vector<std::vector<double>> min_max_set);
    std::vector<std::vector<std::vector<double>>> CalculateNextMinMaxSets(std::vector<std::vector<double>> min_max_set);
    std::vector<int> CalculatePositiveCounts(std::vector<std::vector<double>> min_max_corners);
    int CalculateDimensionDirection(std::vector<double> mid, std::vector<std::vector<double>> min_max_set);

public:
    CalculateCriticalPoints(int subdivision_depth);

};