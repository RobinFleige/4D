#pragma once

#include <vector>
#include "ParameterDependentVectorField.h"
#include "CriticalPoint.h"

class ProcessObject {
    ParameterDependentVectorField* vector_field_;
    std::vector<CriticalPoint*> critical_points_;

public:
    void AppendCriticalPoints(std::vector<CriticalPoint*> critical_points);
    ParameterDependentVectorField* GetVectorField();
    void SetVectorField(ParameterDependentVectorField* vector_field);
    std::vector<CriticalPoint*> GetCriticalPoints();
};