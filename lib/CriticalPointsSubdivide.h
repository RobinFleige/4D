#pragma once
#include <vector>
#include <vtkImageData.h>
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include "../PipelineDefs/Filter.h"

class CriticalPointsSubdivide : public Filter<vtkSmartPointer<vtkImageData>,vtkSmartPointer<vtkPoints>> {
public:
    void InternalUpdate() override;
};