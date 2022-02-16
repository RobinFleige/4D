#pragma once

#include <vector>
class SpaceVector {
private:
    std::vector<double> values_;
public:
    explicit SpaceVector(std::vector<double> values);
    std::vector<double>* GetValues();
};