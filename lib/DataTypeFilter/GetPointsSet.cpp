#include "GetPointsSet.h"

GetPointsSet::GetPointsSet() {
    Invalidate();
}

void GetPointsSet::InternalUpdate() {
    output_ = input_->GetCriticalPoints();
}
