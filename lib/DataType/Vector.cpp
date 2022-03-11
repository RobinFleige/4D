#include "Vector.h"

Vector Vector::Derivative(Vector a, Vector b,  double multiplicator) {
    std::vector<double> derivative;
    derivative.reserve(a.values_.size());
    for(int i = 0; i < a.values_.size(); i++){
        derivative.push_back((a.values_[i]-b.values_[i])*multiplicator);
    }
    auto vec = new Vector();
    vec->values_ = derivative;
    return *vec;
}
