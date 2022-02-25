#include "VectorFieldToImageData.h"

void VectorFieldToImageData::InternalUpdate() {
    output_->SetDimensions(input_->GetSize(),input_->GetSize(),1);
    output_->AllocateScalars(VTK_DOUBLE,3);
    output_->GetPointData()->SetActiveVectors("ImageScalars");
    for(int x = 0; x < input_->GetSize(); x++){
        for(int y = 0; y < input_->GetSize(); y++){
            auto* pixel = static_cast<double*>(output_->GetScalarPointer(x, y, 0));
            const std::vector<double>& values = input_->GetData(x,y);
            pixel[0] = values[0];
            pixel[1] = values[1];
            pixel[2] = 0;
        }
    }
}

VectorFieldToImageData::VectorFieldToImageData() {
    output_ = vtkSmartPointer<vtkImageData>::New();
    Invalidate();
}
