#pragma once
#include <vector>
#include <vtkImageData.h>
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include "../PipelineDefs/Filter.h"

class CriticalPointsSet : public Filter<std::vector<std::vector<vtkSmartPointer<vtkImageData>>>,std::vector<std::vector<vtkSmartPointer<vtkPoints>>>> {
public:
    void InternalUpdate() override;
};