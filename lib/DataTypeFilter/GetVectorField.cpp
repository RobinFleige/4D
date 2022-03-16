#include "GetVectorField.h"

GetVectorField::GetVectorField(int parameter_dimensions) {
    name_ = "Subspace4D2D";
    values_.reserve(parameter_dimensions);
    for(int i = 0; i < parameter_dimensions; i++){
        values_.push_back(0);
    }
    Invalidate();
}

void GetVectorField::SetId(int value, int id) {
    values_[id] = value;
    Invalidate();
}

void GetVectorField::InternalUpdate() {
    output_ = input_->GetVectorField({values_[0],values_[1]});
}

void GetVectorField::OnChange(double value, int id) {
    values_[id] = int(value);
    Invalidate();
    Update();
}