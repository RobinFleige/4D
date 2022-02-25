#pragma once
#include <vector>
#include <vtkImageData.h>
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <Slider/SliderObserver.h>
#include <DataType/VectorField4D.h>
#include <DataType/VectorField2D.h>
#include "../PipelineDefs/Filter.h"
class Subspace4D2D : public Filter<VectorField4D*,VectorField2D*>, public SliderObserver {
private:
    std::vector<int> values_;
    void InternalUpdate() override;

public:
    Subspace4D2D();
    void SetId(int value, int id);
    void OnChange(double value, int id) override;
};