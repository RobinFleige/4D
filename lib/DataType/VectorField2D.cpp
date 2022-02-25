#include <valarray>
#include "VectorField4D.h"

std::vector<std::vector<std::vector<std::vector<std::vector<double>>>>> VectorField4D::GetData() {
    return values_;
}

VectorField4D::VectorField4D(int size) {
    size_ = size;
}

void VectorField4D::SetData(std::vector<std::vector<std::vector<std::vector<std::vector<double>>>>> values) {
    values_ = values;
}

int VectorField4D::GetSize() {
    return size_;
}
