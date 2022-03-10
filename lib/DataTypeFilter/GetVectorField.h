#pragma once
#include <DataType/ProcessObject.h>
#include <PipelineDefs/Filter.h>
#include <DataType/Point.h>

class GetVectorField : public Filter<ProcessObject*, ParameterDependentVectorField*> {
private:
    void InternalUpdate() override;
public:
    GetVectorField();
};