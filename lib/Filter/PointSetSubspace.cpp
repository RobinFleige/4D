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
    for(int i = 0; i < input_->GetCriticalPoints().size(); i++){
        if(input_->GetCriticalPoints()[i]->GetCoordinates()[0] >= s_ && input_->GetCriticalPoints()[i]->GetCoordinates()[0] < s_ && input_->GetCriticalPoints()[i]->GetCoordinates()[1] >= t_ && input_->GetCriticalPoints()[i]->GetCoordinates()[1] < t_+1){
            output_.push_back(input_->GetCriticalPoints()[i]);
        }
    }
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


