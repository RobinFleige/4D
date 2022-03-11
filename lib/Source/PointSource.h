#pragma once
#include <vtkPoints.h>
#include <vtkSmartPointer.h>
#include "PipelineDefs/Source.h"
#include "Slider/SliderObserver.h"
#include "DataType/Point.h"

class PointSource : public Source<std::vector<Point*>>, public SliderObserver {
private:
    std::vector<double> coordinates_;
    void InternalUpdate() override;
public:
    void SetCoordinates(std::vector<double> coordinates);
    PointSource();
    void OnChange(double value, int id) override;
};