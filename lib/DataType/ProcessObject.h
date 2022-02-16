#pragma once

#include <vector>
#include "VectorField.h"
#include "BifurcationPoint.h"

class ProcessObject {
    VectorField* vector_field_;
    std::vector<CriticalPoint*> critical_points_;
    std::vector<BifurcationPoint*> bifurcation_points_;

public:
    void SetCriticalPoints(std::vector<CriticalPoint*> critical_points);
    void AppendCriticalPoints(std::vector<CriticalPoint*> critical_points);
    VectorField* GetVectorField();
    std::vector<CriticalPoint*> GetCriticalPoints();
};