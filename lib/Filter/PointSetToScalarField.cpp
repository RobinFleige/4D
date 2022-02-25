#include "PointSetToScalarField.h"

void PointSetToScalarField::InternalUpdate() {
    output_ = vtkSmartPointer<vtkImageData>::New();

    output_->SetDimensions(size_,size_,1);
    output_->AllocateScalars(VTK_FLOAT, 3);
    for(int i = 0; i < input_.size(); i++) {
        auto* pixel = static_cast<float*>(output_->GetScalarPointer(input_[i]->GetCoordinates()[0],input_[i]->GetCoordinates()[1],0));
        pixel[0] = pixel[0] + 64;
        pixel[1] = pixel[1] + 64;
        pixel[2] = pixel[2] + 64;
    }
}

PointSetToScalarField::PointSetToScalarField(int size) {
    size_ = size;
    Invalidate();
}
