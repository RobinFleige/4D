#pragma once
#include <vtkImageShiftScale.h>
#include <vtkImageDataLIC2D.h>
#include <vtkImageData.h>
#include <vtkSmartPointer.h>
#include <vector>
#include <vtkPoints.h>
#include "../PipelineDefs/DoubleFilter.h"
class DrawPointOnImage : public DoubleFilter<vtkSmartPointer<vtkImageData>,vtkSmartPointer<vtkPoints>,vtkSmartPointer<vtkImageData>> {

};