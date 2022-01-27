#pragma once
#include <vector>
#include <vtkImageData.h>
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include "../PipelineDefs/Filter.h"

class CriticalPointsSet : public Filter<std::vector<std::vector<vtkSmartPointer<vtkImageData>>>,std::vector<std::vector<vtkSmartPointer<vtkPoints>>>> {
private:
    std::vector<std::vector<vtkSmartPointer<vtkPoints>>> points_;
public:

    std::vector<std::vector<vtkSmartPointer<vtkPoints>>> GetInternalOutput() override;
    void InternalUpdate() override;
};