#include <valarray>
#include "VectorField.h"

std::vector<std::vector<std::vector<double>>>& VectorField::GetData() {
    return values_;
}

VectorField::VectorField(int size) {
    size_ = size;
}

void VectorField::SetData(std::vector<std::vector<std::vector<double>>> values) {
    values_ = std::move(values);
}

int VectorField::GetSize() {
    return size_;
}

std::vector<double>& VectorField::GetData(int x, int y) {
    return values_[x][y];
}
