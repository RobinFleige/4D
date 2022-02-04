#pragma once
#include <vtkImageShiftScale.h>
#include <vtkImageDataLIC2D.h>
#include <vtkImageData.h>
#include <vtkSmartPointer.h>
#include <vector>
#include <vtkPoints.h>
#include "../PipelineDefs/DoubleFilter.h"

class DrawPointsOnImage : public DoubleFilter<vtkSmartPointer<vtkImageData>,vtkSmartPointer<vtkPoints>,vtkSmartPointer<vtkImageData>>{
private:
    void InternalUpdate() override;
public:
    DrawPointsOnImage();
};