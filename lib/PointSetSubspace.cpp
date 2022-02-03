#include "PointSetSubspace.h"

void PointSetSubspace::SetSValue(int s){
    s_ = s;
    Invalidate();
}
void PointSetSubspace::SetTValue(int t){
    t_ = t;
    Invalidate();
}

void PointSetSubspace::InternalUpdate() {
    input_ = input_connection_->GetOutput();
    output_ = input_[s_][t_];
}

void PointSetSubspace::OnChange(double value, int id) {
    if(id == 0){
        s_ = value;
    }else if(id == 1){
        t_ = value;
    }
    Invalidate();
    Update();
}

PointSetSubspace::PointSetSubspace() {
    s_ = 0;
    t_ = 0;
    Invalidate();
}


