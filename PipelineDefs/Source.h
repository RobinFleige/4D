#pragma once
#include "HasOutput.h"
template<class S>class Source : public HasOutput<S> {
protected:
    bool updatable_ = true;
    virtual void InternalUpdate() = 0;

public:
    virtual S GetInternalOutput() = 0;

    virtual void Update(){
        if(updatable_){
            InternalUpdate();
            updatable_ = false;
        }
    }

    virtual S GetOutput() {
        Update();
        return GetInternalOutput();
    }
};