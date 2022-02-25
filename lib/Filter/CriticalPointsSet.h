#pragma once
#include <vector>
#include <vtkImageData.h>
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include "../PipelineDefs/Filter.h"
#include "../DataType/CriticalPoint.h"
#include "../DataType/VectorField4D.h"
#include "../DataType/ProcessObject.h"

class CriticalPointsSet : public Filter<VectorField4D*,ProcessObject*> {
private:
    bool Subdivide(int max_iterations, std::vector<std::vector<double>> pixel);
    void InternalUpdate() override;
public:
    CriticalPointsSet();
};