#pragma once
#include <vtkImageData.h>
#include <vtkSmartPointer.h>
#include <vector>
#include "../PipelineDefs/Filter.h"
#include "SliderObserver.h"

class Subspace : public Filter<std::vector < std::vector < vtkSmartPointer < vtkImageData>>>,vtkSmartPointer<vtkImageData>>, public SliderObserver{
private:
    int s_;
    int t_;

    void InternalUpdate() override;

public:
    void SetTValue(int t);
    void SetSValue(int s);
    void OnChange(double value, int id) override;
    Subspace();

};