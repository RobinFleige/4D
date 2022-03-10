#pragma once
#include <vector>
#include <vtkImageData.h>
#include "../PipelineDefs/Source.h"
#include "../DataType/ParameterDependentVectorField.h"
#include "../DataType/ProcessObject.h"
#include <vtkPointData.h>

class VectorFieldSource : public Source<ProcessObject*>{
private:
    int parameter_dimensions_ = 2;
    int space_dimensions_ = 2;
    int dimensions_ = 4;

    int size_;
    double min_;
    double max_;
    double step_;

    double Function(std::vector<int> parameters, int space_dimension);
    double Normalize(int i) const;
    void InternalUpdate() override;
public:
    VectorFieldSource(int size, double min, double max);

};