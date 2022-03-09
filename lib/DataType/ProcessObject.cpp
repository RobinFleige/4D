#include "ProcessObject.h"

ParameterDependentVectorField* ProcessObject::GetVectorField() {
    return vector_field_;
}

std::vector<CriticalPoint*> ProcessObject::GetCriticalPoints() {
    return critical_points_;
}

void ProcessObject::AppendCriticalPoints(std::vector<CriticalPoint *> critical_points) {
    for(int i = 0; i < critical_points.size(); i++){
        critical_points_.push_back(critical_points[i]);
    }
}

void ProcessObject::SetVectorField(ParameterDependentVectorField *vector_field) {
    vector_field_ = vector_field;
}
