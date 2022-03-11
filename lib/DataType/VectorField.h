#pragma once
#include <valarray>
#include "Vector.h"

class VectorField {
private:
    std::vector<Vector> vectors_;

    int dimensions_;
    int size_;

    int IDFromIDs(std::vector<int> ids);
    std::vector<int> IDsFromID(int id);
public:
    explicit VectorField(int dimensions, int size);
    void SetData(std::vector<Vector> vectors);
    Vector GetData(std::vector<int> ids);
    Vector GetInterpolated(std::vector<double> ids);
    int GetSize() const;
};