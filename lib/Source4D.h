#include <vector>
#include <vtkImageData.h>
#include "../PipelineDefs/Source.h"
#pragma once
#include <vtkPointData.h>

class Source4D : public Source<std::vector<std::vector<vtkSmartPointer<vtkImageData>>>>{
private:
    int width_;
    int param_width_;

    //s,t,image
    std::vector<std::vector<vtkSmartPointer<vtkImageData>>> vector_field;


    float x_function(int x, int y, int s, int t);
    float y_function(int x, int y, int s, int t);
    std::vector<std::vector<vtkSmartPointer<vtkImageData>>> GetInternalOutput();
    void InternalUpdate();
public:
    Source4D();
    void SetWidth(int width);
    void SetParamWidth(int param_width);

};


