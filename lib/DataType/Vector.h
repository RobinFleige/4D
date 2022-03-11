#pragma once
#include <vector>

class Vector {
public:
    std::vector<double> values_;
    static Vector Derivative(Vector a, Vector b, double multiplicator);
};