#include "PointSetToScalarField.h"

vtkSmartPointer<vtkImageData> PointSetToScalarField::GetInternalOutput() {
    return image_;
}

void PointSetToScalarField::InternalUpdate() {
    input_ = input_connection_->GetOutput();
    image_ = vtkSmartPointer<vtkImageData>::New();
    image_->SetDimensions(input_.size(),input_[0].size(),1);
    image_->AllocateScalars(VTK_FLOAT, 1);
    for(int x = 0; x < input_.size(); x++) {
        for (int y = 0; y < input_[0].size(); y++) {
            float* pixel = static_cast<float*>(image_->GetScalarPointer(x,y,0));
            pixel[0] = input_[x][y]->GetNumberOfPoints() * 64;
        }
    }
}
