#pragma once
#include <vector>
#include <vtkImageData.h>
#include <vtkSmartPointer.h>
#include "../PipelineDefs/Source.h"
#include <DataType/ProcessObject.h>

class TestSource : public Source<ProcessObject*>{
private:
    int size_;
    double min_ = -2;
    double max_ = 2;
    double step_;
    void InternalUpdate() override;
    double Normalize(int i) const;
public:
    explicit TestSource(int size);
};