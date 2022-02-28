#pragma once
#include <vector>
#include <vtkImageData.h>
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include "../PipelineDefs/Filter.h"
#include "../DataType/CriticalPoint.h"
#include "../DataType/VectorField4D.h"
#include "../DataType/ProcessObject.h"

class CalculateCriticalPoints : public Filter<VectorField4D*,ProcessObject*> {
private:
    std::vector<CriticalPoint*> Subdivide(bool interpolate, int max_iterations, std::vector<std::vector<double>> ids);
    void InternalUpdate() override;
public:
    CalculateCriticalPoints();
};