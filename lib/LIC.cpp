#include "./LIC.h"

vtkSmartPointer<vtkImageData> LIC::GetInternalOutput() {
    return scale->GetOutput();
}
void LIC::InternalUpdate() {
    lic->SetInputData(input_connection_->GetOutput());
    lic->Update();
    scale->SetInputData(lic->GetOutput());
    scale->SetScale(128);
    scale->Update();
}