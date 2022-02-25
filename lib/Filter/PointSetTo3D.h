#pragma once
#include <vector>
#include <vtkImageData.h>
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <DataType/Point.h>
#include <DataType/CriticalPoint.h>
#include "../PipelineDefs/Filter.h"

class PointSetTo3D : public Filter<std::vector<CriticalPoint*>,std::vector<vtkSmartPointer<vtkImageData>>> {
private:
    int id_;
    int size_;
    int dimensions_ = 4;
    void InternalUpdate() override;
public:
    void SetParameterID(int id);
    PointSetTo3D(int size);
};