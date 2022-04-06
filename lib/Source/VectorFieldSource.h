#pragma once
#include <vector>
#include <vtkImageData.h>
#include "../PipelineDefs/Source.h"
#include "../DataType/ParameterDependentVectorField.h"
#include <vtkPointData.h>

enum VectorFieldExampleType{simple2d2d_without_y,simple2d2d,circle2d2d,double2d2d,simple2d3d,simple3d2d,circle3d2d,simple3d3d,simple2d4d,simple4d2d};

class VectorFieldSource : public Source<ParameterDependentVectorField*>{
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
    VectorFieldSource(int size, double min, double max, VectorFieldExampleType type);

};