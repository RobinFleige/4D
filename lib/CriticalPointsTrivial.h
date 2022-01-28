#pragma once
#include <vtkImageData.h>
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include "../PipelineDefs/Filter.h"

class CriticalPointsTrivial : public Filter<vtkSmartPointer<vtkImageData>,vtkSmartPointer<vtkPoints>> {
private:
    double threshold_ = 0.0000000000000000000000000000000000001;
public:
    void InternalUpdate() override;
    void SetThreshold(double threshold);
};