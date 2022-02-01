#include "PointSetToScalarField.h"

void PointSetToScalarField::InternalUpdate() {
    input_ = input_connection_->GetOutput();
    output_ = vtkSmartPointer<vtkImageData>::New();
    output_->SetDimensions(input_.size(),input_[0].size(),1);
    output_->AllocateScalars(VTK_FLOAT, 1);
    for(int x = 0; x < input_.size(); x++) {
        for (int y = 0; y < input_[0].size(); y++) {
            auto* pixel = static_cast<float*>(output_->GetScalarPointer(x,y,0));
            pixel[0] = input_[x][y]->GetNumberOfPoints() * 64;
        }
    }
}
