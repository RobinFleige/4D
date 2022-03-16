#pragma once
#include <vector>
#include <vtkImageData.h>
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <Slider/SliderObserver.h>
#include <DataType/ParameterDependentVectorField.h>
#include <DataType/VectorField.h>
#include "PipelineDefs/Filter.h"
class GetVectorField : public Filter<ParameterDependentVectorField*,VectorField*>, public SliderObserver {
private:
    std::vector<int> values_;
    void InternalUpdate() override;

public:
    explicit GetVectorField(int parameter_dimensions);
    void SetId(int value, int id);
    void OnChange(double value, int id) override;
};