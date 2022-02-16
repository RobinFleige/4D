#pragma once
#include <vtkImageShiftScale.h>
#include <vtkImageDataLIC2D.h>
#include <vtkImageData.h>
#include <vtkSmartPointer.h>
#include "../../PipelineDefs/Filter.h"

class LIC : public Filter<vtkSmartPointer<vtkImageData>,vtkSmartPointer<vtkImageData>> {
private:
    vtkSmartPointer<vtkImageDataLIC2D> lic;
    vtkSmartPointer<vtkImageShiftScale> scale;

    void InternalUpdate() override;
public:
    LIC();
};