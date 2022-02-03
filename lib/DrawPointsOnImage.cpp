#include "DrawPointsOnImage.h"

void DrawPointsOnImage::InternalUpdate() {
    input_ = input_connection_->GetOutput();
    secondary_input_ = secondary_input_connection_->GetOutput();
    output_ = input_;

    double point[3];
    for(int i = 0; i < secondary_input_->GetNumberOfPoints(); i++){
        secondary_input_->GetPoint(i,point);
        auto* pixel = static_cast<float*>(output_->GetScalarPointer(point[0], point[1], 0));
        pixel[0] = 255;
        pixel[1] = 0.0;
        pixel[2] = 0.0;
    }
}
