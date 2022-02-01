#include <vector>
#include <vtkImageData.h>
#include "../PipelineDefs/Source.h"
#pragma once
#include <vtkPointData.h>

class Source4D : public Source<std::vector<std::vector<vtkSmartPointer<vtkImageData>>>>{
private:
    int width_;
    int param_width_;
    double min_;
    double max_;
    double step_;

    float x_function(int x, int y, int s, int t);
    float y_function(int x, int y, int s, int t);
    double normalize(int i) const;
    std::vector<std::vector<vtkSmartPointer<vtkImageData>>> GetInternalOutput();
    void InternalUpdate() override;
public:
    Source4D(int width, double min, double max);

};


