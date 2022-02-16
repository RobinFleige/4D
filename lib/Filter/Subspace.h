#pragma once
#include <vtkImageData.h>
#include <vtkSmartPointer.h>
#include <vector>
#include "../../PipelineDefs/Filter.h"
#include "Source/Slider/SliderObserver.h"
#include "../DataType/ProcessObject.h"

class Subspace : public Filter<VectorField*,VectorField*>, public SliderObserver{
private:
    std::vector<int> parameters_;

    void InternalUpdate() override;

public:
    void SetParameters(std::vector<int> parameters);
    void OnChange(double value, int id) override;
    Subspace();

};