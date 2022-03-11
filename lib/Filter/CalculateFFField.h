#pragma once
#include <vector>
#include <DataType/ProcessObject.h>
#include "../PipelineDefs/Filter.h"
#include "DataType/Point.h"

class CalculateFFField : public Filter<ProcessObject*,ProcessObject*> {
private:
    void InternalUpdate() override;
    double Determinant(std::vector<std::vector<double>> matrix);
public:
    CalculateFFField();
};