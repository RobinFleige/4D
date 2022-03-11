#pragma once
#include <vector>
#include <vtkImageData.h>
#include "../PipelineDefs/Source.h"
#include "../DataType/ParameterDependentVectorField.h"
#include "../DataType/ProcessObject.h"
#include <vtkPointData.h>

enum VectorFieldExampleType{simple4d_without_y,simple4d,circle4d,double4d,simple5d};

class VectorFieldSource : public Source<ProcessObject*>{
private:
    int parameter_dimensions_;
    int space_dimensions_;

    VectorFieldExampleType type_;
    int size_;
    double min_;
    double max_;
    double step_;

    double Normalize(int i) const;
    void InternalUpdate() override;
public:
    VectorFieldSource(int parameter_dimension, int space_dimensions, int size, double min, double max,VectorFieldExampleType type);

};