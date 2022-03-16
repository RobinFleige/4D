#pragma once
#include <DataType/ParameterDependentVectorField.h>
#include <PipelineDefs/Filter.h>
#include <DataType/Point.h>

class GetPointsSet : public Filter<ParameterDependentVectorField*, std::vector <CriticalPoint*>> {
private:
    void InternalUpdate() override;
public:
    GetPointsSet();

};