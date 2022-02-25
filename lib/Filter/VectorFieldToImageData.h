#pragma once
#include <vector>
#include <vtkImageData.h>
#include <vtkPointData.h>
#include <vtkSmartPointer.h>
#include "../DataType/VectorField2D.h"
#include "../PipelineDefs/Filter.h"


class VectorFieldToImageData : public Filter<VectorField2D*, vtkSmartPointer<vtkImageData>>{
public:
    VectorFieldToImageData();
    void InternalUpdate() override;
};