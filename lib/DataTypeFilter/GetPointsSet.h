#pragma once
#include <DataType/ProcessObject.h>
#include <PipelineDefs/Filter.h>
#include <DataType/Point.h>

class GetPointsSet : public Filter<ProcessObject*, std::vector <CriticalPoint*>> {
private:
    void InternalUpdate() override;
public:
    GetPointsSet();

};