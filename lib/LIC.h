#pragma once
#include <vtkImageShiftScale.h>
#include <vtkImageDataLIC2D.h>
#include <vtkImageData.h>
#include <vtkSmartPointer.h>
#include "../PipelineDefs/Filter.h"

class LIC : public Filter<vtkSmartPointer<vtkImageData>,vtkSmartPointer<vtkImageData>> {
private:
    vtkNew<vtkImageDataLIC2D> lic;
    vtkNew<vtkImageShiftScale> scale;

    vtkSmartPointer<vtkImageData> GetInternalOutput() override;
    void InternalUpdate() override;
};