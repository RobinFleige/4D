#include "CriticalPointsTrivial.h"

void CriticalPointsTrivial::InternalUpdate() {
    output_ = vtkSmartPointer<vtkPoints>::New();
    input_connection_->Update();
    vtkSmartPointer<vtkImageData> input = input_connection_->GetOutput();
    for(int x = 0; x < input->GetDimensions()[0]; x++){
        for(int y = 0; y < input->GetDimensions()[1]; y++){
            double* pixel = static_cast<double*>(input->GetScalarPointer(x,y,0));
            if(pixel[0]*pixel[0]+pixel[1]*pixel[1] < threshold_){
                output_->InsertNextPoint(x,y,0);
            }
        }
    }
}

void CriticalPointsTrivial::SetThreshold(double threshold) {
    threshold_ = threshold;
    this->Invalidate();
}
