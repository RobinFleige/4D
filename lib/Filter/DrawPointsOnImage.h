#pragma once
#include <vtkImageShiftScale.h>
#include <vtkImageDataLIC2D.h>
#include <vtkImageData.h>
#include <vtkSmartPointer.h>
#include <vector>
#include <vtkPoints.h>
#include "../PipelineDefs/DoubleFilter.h"
#include "DataType/Point.h"

class DrawPointsOnImage : public DoubleFilter<vtkSmartPointer<vtkImageData>,std::vector<Point*>,vtkSmartPointer<vtkImageData>>{
private:
    void InternalUpdate() override;
public:
    DrawPointsOnImage();
};