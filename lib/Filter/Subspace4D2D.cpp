#include "Subspace4D2D.h"

Subspace4D2D::Subspace4D2D() {
    values_={0,0};
    Invalidate();
}

void Subspace4D2D::SetId(int value, int id) {
    values_[id] = value;
    Invalidate();
}

void Subspace4D2D::InternalUpdate() {
    output_ = new VectorField(input_->GetSize());
    output_->SetData(input_->GetData(values_[0],values_[1]));
}

void Subspace4D2D::OnChange(double value, int id) {
    values_[id] = int(value);
    Invalidate();
    Update();
}