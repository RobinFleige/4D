#include "Subspace.h"

void Subspace::SetSValue(int s){
    s_ = s;
}
void Subspace::SetTValue(int t){
    t_ = t;
}

void Subspace::InternalUpdate() {}

vtkSmartPointer<vtkImageData> Subspace::GetInternalOutput(){
    return input_connection_->GetOutput()[s_][t_];
}

void Subspace::OnChange(double value, int id) {
    if(id == 0){
        s_ = value;
    }else if(id == 1){
        t_ = value;
    }
    Update();
}
