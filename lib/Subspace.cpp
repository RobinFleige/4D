#include "Subspace.h"

void Subspace::SetSValue(int s){
    s_ = s;
    Invalidate();
}
void Subspace::SetTValue(int t){
    t_ = t;
    Invalidate();
}

void Subspace::InternalUpdate() {
    input_ = input_connection_->GetOutput();
    output_ = input_[s_][t_];
}



void Subspace::OnChange(double value, int id) {
    if(id == 0){
        s_ = value;
    }else if(id == 1){
        t_ = value;
    }
    Update();
}

Subspace::Subspace() {
    s_ = 0;
    t_ = 0;
    Invalidate();
}


