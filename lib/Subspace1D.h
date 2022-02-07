#pragma once
#include <vtkImageData.h>
#include <vtkSmartPointer.h>
#include <vector>
#include "../PipelineDefs/Filter.h"
#include "SliderObserver.h"

class Subspace1D : public Filter<std::vector < vtkSmartPointer < vtkImageData>>,vtkSmartPointer<vtkImageData>>, public SliderObserver{
private:
    int s_;

    void InternalUpdate() override;

public:
    void SetSValue(int s);
    void OnChange(double value, int id) override;
    Subspace1D();

};