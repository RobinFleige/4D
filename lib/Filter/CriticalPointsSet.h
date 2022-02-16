#pragma once
#include <vector>
#include <vtkImageData.h>
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include "../PipelineDefs/Filter.h"
#include "../DataType/CriticalPoint.h"
#include "../DataType/VectorField.h"
#include "../DataType/ProcessObject.h"

class CriticalPointsSet : public Filter<VectorField*,ProcessObject*> {
public:
    std::vector<CriticalPoint*> Subdivide(int min_iterations, int max_iterations, std::vector<std::vector<double>> pixel);
    void InternalUpdate() override;
};