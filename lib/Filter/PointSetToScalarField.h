#pragma once
#include <vector>
#include <vtkImageData.h>
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <DataType/Point.h>
#include "../PipelineDefs/Filter.h"

class PointSetToScalarField : public Filter<std::vector<Point*>,vtkSmartPointer<vtkImageData>> {
private:
    int parameter_dimension_ = 2;
    int size_;
    void InternalUpdate() override;
public:
    PointSetToScalarField(int size);
};