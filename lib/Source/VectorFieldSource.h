#pragma once
#include <vector>
#include <vtkImageData.h>
#include "../PipelineDefs/Source.h"
#include "../DataType/VectorField.h"
#include "../DataType/SpaceVector.h"
#include <vtkPointData.h>

class VectorFieldSource : public Source<VectorField*>{
private:
    int parameter_dimensions_;
    int space_dimensions_;

    std::vector<int> widths_;
    std::vector<double> mins_;
    std::vector<double> maxs_;
    std::vector<double> steps_;

    double Function(std::vector<int> parameters, int space_dimension);
    double Normalize(int i, int param_id) const;
    void InternalUpdate() override;
public:
    VectorFieldSource(int parameter_dimensions, int space_dimensions, std::vector<int> widths, std::vector<double> mins, std::vector<double> maxs);

};