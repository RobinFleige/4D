#pragma once
#include <vector>
#include <DataType/ProcessObject.h>
#include "../PipelineDefs/Filter.h"
#include "DataType/Point.h"

class FFF : public Filter<ProcessObject*,ProcessObject*> {
private:
    void InternalUpdate() override;
public:
    FFF();
};