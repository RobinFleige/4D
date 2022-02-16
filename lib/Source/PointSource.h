#pragma once
#include <vtkPoints.h>
#include <vtkSmartPointer.h>
#include "PipelineDefs/Source.h"
#include "Slider/SliderObserver.h"
#include "DataType/Point.h"

class PointSource : public Source<std::vector<Point*>>, public SliderObserver {
private:
    int x_;
    int y_;
    void InternalUpdate() override;
public:
    void SetX(int x);
    void SetY(int y);
    PointSource();
    void OnChange(double value, int id) override;
};