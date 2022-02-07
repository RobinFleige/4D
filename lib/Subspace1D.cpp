#include "Subspace1D.h"

void Subspace1D::SetSValue(int s){
    s_ = s;
    Invalidate();
}

void Subspace1D::InternalUpdate() {
    input_ = input_connection_->GetOutput();
    output_ = input_[s_];
}



void Subspace1D::OnChange(double value, int id) {
    if(id == 0){
        s_ = value;
    }
    Invalidate();
    Update();
}

Subspace1D::Subspace1D() {
    s_ = 0;
    Invalidate();
}


