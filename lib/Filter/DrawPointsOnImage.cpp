#include "DrawPointsOnImage.h"

void DrawPointsOnImage::InternalUpdate() {
    input_ = input_connection_->GetOutput();
    secondary_input_ = secondary_input_connection_->GetOutput();
    output_->DeepCopy(input_);

    for(int i = 0; i < secondary_input_.size(); i++){
        auto* pixel = static_cast<float*>(output_->GetScalarPointer(secondary_input_[i]->GetCoordinates()[0], secondary_input_[i]->GetCoordinates()[1], 0));
        pixel[0] = 255;
        pixel[1] = 0.0;
        pixel[2] = 0.0;
    }
}

DrawPointsOnImage::DrawPointsOnImage() {
    output_ = vtkSmartPointer<vtkImageData>::New();
    Invalidate();
}
