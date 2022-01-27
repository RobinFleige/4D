#pragma once
#include <vector>
#include <vtkImageData.h>
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include "../PipelineDefs/Filter.h"

class CriticalPointsSubdivide : public Filter<vtkSmartPointer<vtkImageData>,vtkSmartPointer<vtkPoints>> {
private:
    vtkSmartPointer<vtkPoints> critical_points_;
public:

    vtkSmartPointer<vtkPoints> GetInternalOutput() override;
    void InternalUpdate() override;
};