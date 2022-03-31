#include <DataType/ParameterDependentVectorField.h>
#include <PipelineDefs/Filter.h>

class ReformDimension : public Filter<ParameterDependentVectorField*,ParameterDependentVectorField*> {
public:
    ReformDimension();
    void InternalUpdate() override;
};