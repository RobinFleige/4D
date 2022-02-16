#pragma once
#include <vector>
#include <vtkImageData.h>
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include "../PipelineDefs/Filter.h"
#include "DataType/ProcessObject.h"

class PointSetToScalarField : public Filter<ProcessObject*,vtkSmartPointer<vtkImageData>> {
private:
    void InternalUpdate() override;
};