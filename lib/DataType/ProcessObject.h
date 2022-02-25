#pragma once

#include <vector>
#include "VectorField4D.h"
#include "BifurcationPoint.h"

class ProcessObject {
    VectorField4D* vector_field_;
    std::vector<CriticalPoint*> critical_points_;
    std::vector<BifurcationPoint*> bifurcation_points_;

public:
    void AppendCriticalPoints(std::vector<CriticalPoint*> critical_points);
    VectorField4D* GetVectorField();
    void SetVectorField(VectorField4D* vector_field);
    std::vector<CriticalPoint*> GetCriticalPoints();
};