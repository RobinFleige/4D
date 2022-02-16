#include "PointSetToScalarField.h"

void PointSetToScalarField::InternalUpdate() {
    input_ = input_connection_->GetOutput();
    output_ = vtkSmartPointer<vtkImageData>::New();
    std::vector<int> dimensions;
    for(int i = 0; i < input_->GetVectorField()->GetParameterDimensions(); i++){
        dimensions.push_back(input_->GetVectorField()->GetLengths()[i]);
    }
    output_->SetDimensions(dimensions[0],dimensions[1],1);
    output_->AllocateScalars(VTK_FLOAT, 3);
    for(int i = 0; i < input_->GetCriticalPoints().size(); i++) {
        auto* pixel = static_cast<float*>(output_->GetScalarPointer(input_->GetCriticalPoints()[i]->GetCoordinates()[0],input_->GetCriticalPoints()[i]->GetCoordinates()[1],0));
        pixel[0] = pixel[0] + 64;
        pixel[1] = pixel[1] + 64;
        pixel[2] = pixel[2] + 64;
    }
}
