#pragma once
#include <vtkImageData.h>
#include <vtkSmartPointer.h>
#include <vector>
#include <vtkPoints.h>
#include "../../PipelineDefs/Filter.h"
#include "Source/Slider/SliderObserver.h"

class PointSetSubspace : public Filter<std::vector < std::vector < vtkSmartPointer < vtkPoints>>>,vtkSmartPointer<vtkPoints>>, public SliderObserver{
private:
    int s_;
    int t_;

    void InternalUpdate() override;

public:
    void SetTValue(int t);
    void SetSValue(int s);
    void OnChange(double value, int id) override;
    PointSetSubspace();

};