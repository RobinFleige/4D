#include "Subspace2D.h"

void Subspace2D::SetSValue(int s){
    s_ = s;
    Invalidate();
}
void Subspace2D::SetTValue(int t){
    t_ = t;
    Invalidate();
}

void Subspace2D::InternalUpdate() {
    input_ = input_connection_->GetOutput();
    output_ = input_[s_][t_];
}



void Subspace2D::OnChange(double value, int id) {
    if(id == 0){
        s_ = value;
    }else if(id == 1){
        t_ = value;
    }
    Invalidate();
    Update();
}

Subspace2D::Subspace2D() {
    s_ = 0;
    t_ = 0;
    Invalidate();
}


