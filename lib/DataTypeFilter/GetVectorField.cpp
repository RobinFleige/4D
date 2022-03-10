#include "GetVectorField.h"

GetVectorField::GetVectorField() {
    Invalidate();
}

void GetVectorField::InternalUpdate() {
    output_ = input_->GetVectorField();
}
