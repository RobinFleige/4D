#pragma once
#include <vector>
#include <vtkImageData.h>
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include "../../PipelineDefs/Filter.h"

class PointSetTo3D : public Filter<std::vector<std::vector<vtkSmartPointer<vtkPoints>>>,std::vector<vtkSmartPointer<vtkImageData>>> {
private:
    int id_;
public:
    void InternalUpdate() override;
    void SetParameterID(int id);
};