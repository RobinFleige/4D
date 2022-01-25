#pragma once
#include <vtkImageData.h>
#include <vtkSmartPointer.h>
#include <vector>
#include "../PipelineDefs/Filter.h"

class Subspace : public Filter<std::vector < std::vector < vtkSmartPointer < vtkImageData>>>,vtkSmartPointer<vtkImageData>> {
private:
    int s_;
    int t_;

    vtkSmartPointer<vtkImageData> GetInternalOutput();
    void InternalUpdate();

public:
    void SetTValue(int t);
    void SetSValue(int s);

};