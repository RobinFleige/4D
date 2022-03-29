#pragma once
#include <vector>
#include <vtkImageData.h>
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include "../PipelineDefs/Filter.h"
#include "../DataType/Point.h"
#include "../DataType/ParameterDependentVectorField.h"

class CalculateBifurcationPoints : public Filter<ParameterDependentVectorField*,ParameterDependentVectorField*> {
private:
    bool calculate_critical_points_ = true;
    int subdivision_depth_;
    int param_subdivision_depth_ = 0;

    std::vector<Point*> Subdivide(int max_param_iterations, int max_iterations, std::vector<std::vector<double>> ids);
    void InternalUpdate() override;

    bool OnRightBorder(std::vector<int> ids);
    std::vector<std::vector<double>> CalculateMinMaxSet(std::vector<int> ids);
    std::vector<std::vector<double>> CalculateMinMaxCorners(std::vector<std::vector<double>> min_max_set);
    std::vector<std::vector<std::vector<double>>> CalculateNextMinMaxSets(std::vector<std::vector<double>> min_max_set, bool subdivide_parameters);
    std::vector<int> CalculatePositiveCounts(std::vector<std::vector<double>> min_max_corners);
    int CalculateDimensionDirection(std::vector<double> mid, std::vector<std::vector<double>> min_max_set);

public:
    CalculateBifurcationPoints(int param_subdivision_depth, int subdivision_depth);
    void SetCalculateCriticalPoints(bool calculate_critical_points);

};