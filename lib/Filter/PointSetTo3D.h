#pragma once
#include <vector>
#include <vtkImageData.h>
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include "../PipelineDefs/Filter.h"

class PointSetTo3D : public Filter<std::vector<std::vector<int>>,std::vector<vtkSmartPointer<vtkImageData>>> {
private:
    int id_;
    int size_;
    void InternalUpdate() override;
public:
    void SetParameterID(int id);
    PointSetTo3D(int size);
};