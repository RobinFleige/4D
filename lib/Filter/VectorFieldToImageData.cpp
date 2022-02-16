#include "VectorFieldToImageData.h"

void VectorFieldToImageData::InternalUpdate() {
    if(input_->GetDimensions() != 2){
        return;
    }
    output_->SetDimensions(input_->GetLengths()[0],input_->GetLengths()[1],1);
    output_->AllocateScalars(VTK_DOUBLE,3);
    for(int x = 0; x < input_->GetLengths()[0]; x++){
        for(int y = 0; y < input_->GetLengths()[1]; y++){
            auto* pixel = static_cast<double*>(output_->GetScalarPointer(x, y, 0));
            std::vector<double> values = *input_->GetData()[input_->IDFromIDs({x,y})]->GetValues();
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
