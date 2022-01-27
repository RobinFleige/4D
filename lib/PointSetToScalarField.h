#pragma once
#include <vector>
#include <vtkImageData.h>
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include "../PipelineDefs/Filter.h"

class PointSetToScalarField : public Filter<std::vector<std::vector<vtkSmartPointer<vtkPoints>>>,vtkSmartPointer<vtkImageData>> {
private:
    std::vector<std::vector<vtkSmartPointer<vtkPoints>>> input_;
    vtkSmartPointer<vtkImageData> image_;
public:

    vtkSmartPointer<vtkImageData> GetInternalOutput() override;
    void InternalUpdate() override;
};