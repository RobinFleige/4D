#pragma once
#include <vtkSmartPointer.h>

template<class S> class HasOutput{
public:
    virtual S GetOutput() = 0;
    virtual void Update() = 0;
};