#include "./LIC.h"

LIC::LIC() {
    lic = vtkSmartPointer<vtkImageDataLIC2D>::New();
    scale = vtkSmartPointer<vtkImageShiftScale>::New();
    updatable_ = true;
}

void LIC::InternalUpdate() {
    input_ = input_connection_->GetOutput();
    lic->SetInputData(input_);
    lic->Update();
    scale->SetInputData(lic->GetOutput());
    scale->SetScale(128);
    scale->Update();
    output_ = scale->GetOutput();
}

