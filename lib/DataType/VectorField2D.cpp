#include <valarray>
#include "VectorField2D.h"

std::vector<std::vector<std::vector<double>>>& VectorField2D::GetData() {
    return values_;
}

VectorField2D::VectorField2D(int size) {
    size_ = size;
}

void VectorField2D::SetData(std::vector<std::vector<std::vector<double>>> values) {
    values_ = std::move(values);
}

int VectorField2D::GetSize() {
    return size_;
}

std::vector<double>& VectorField2D::GetData(int x, int y) {
    return values_[x][y];
}
