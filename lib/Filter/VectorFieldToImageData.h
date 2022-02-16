#pragma once
#include <vector>
#include <vtkImageData.h>
#include <vtkSmartPointer.h>
#include "../DataType/VectorField.h"
#include "../PipelineDefs/Filter.h"


class VectorFieldToImageData : public Filter<VectorField*, vtkSmartPointer<vtkImageData>>{
public:
    VectorFieldToImageData();
    void InternalUpdate() override;
};