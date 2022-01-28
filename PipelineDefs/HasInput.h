#pragma once
#include "HasOutput.h"
template<class InputType> class HasInput : public Updatable{
protected:
    HasOutput<InputType>* input_connection_;
    InputType input_;
public:
    void SetInputConnection(HasOutput<InputType>* input_connection){
        input_connection_ = input_connection;
        input_connection_->AddOutputConnection(this);
        this->Invalidate();
    }
};