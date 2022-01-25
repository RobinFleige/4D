#pragma once
#include "HasOutput.h"

template<class T, class S> class Filter : public HasOutput<S> {
protected:
    HasOutput<T>* input_connection_;
    bool updatable_ = true;
    virtual void InternalUpdate() = 0;
    virtual S GetInternalOutput() = 0;

public:
    virtual void SetInputConnection(HasOutput<T>* input_connection){
        input_connection_ = input_connection;
        updatable_ = true;
    }

    virtual void Update(){
        if(input_connection_){
            input_connection_->Update();
        }
        if(updatable_){
            InternalUpdate();
            updatable_ = false;
        }
    }

    virtual S GetOutput() {
        if (updatable_) {
            Update();
        }
        return GetInternalOutput();
    }
};