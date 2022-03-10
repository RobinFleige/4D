#pragma once
#include <vector>
#include <vtkImageData.h>
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include "../PipelineDefs/Filter.h"
#include "../DataType/CriticalPoint.h"
#include "../DataType/ParameterDependentVectorField.h"
#include "../DataType/ProcessObject.h"

class CalculateBifurcationPoints : public Filter<ProcessObject*,ProcessObject*> {
private:
    bool calculate_critical_points_ = true;

    std::vector<CriticalPoint*> Subdivide(int max_iterations, std::vector<std::vector<double>> ids);
    void InternalUpdate() override;
public:
    CalculateBifurcationPoints();
    void SetCalculateCriticalPoints(bool calculate_critical_points);
};