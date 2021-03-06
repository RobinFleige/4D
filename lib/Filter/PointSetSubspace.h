#pragma once
#include <vtkImageData.h>
#include <vtkSmartPointer.h>
#include <vector>
#include <vtkPoints.h>
#include "../PipelineDefs/Filter.h"
#include "../Slider/SliderObserver.h"
#include "DataType/ParameterDependentVectorField.h"

class PointSetSubspace : public Filter<ParameterDependentVectorField*,std::vector<Point*>>, public SliderObserver{
private:
    double s_;
    double t_;

    void InternalUpdate() override;

public:
    void SetTValue(int t);
    void SetSValue(int s);
    void OnChange(double value, int id) override;
    PointSetSubspace();

};