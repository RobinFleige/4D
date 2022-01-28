#include "./LIC.h"

LIC::LIC() {
    lic = vtkSmartPointer<vtkImageDataLIC2D>::New();
    scale = vtkSmartPointer<vtkImageShiftScale>::New();
}

void LIC::InternalUpdate() {
    lic->SetInputData(input_connection_->GetOutput());
    lic->Update();
    scale->SetInputData(lic->GetOutput());
    scale->SetScale(128);
    scale->Update();
    output_ = scale->GetOutput();
}

