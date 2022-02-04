#pragma once
#include "HasInput.h"
#include "HasOutput.h"
template<class InputType1, class InputType2> class HasSecondaryInput : public HasInput<InputType1>{
protected:
    HasOutput<InputType2>* secondary_input_connection_;
    InputType2 secondary_input_;
public:
    void SetSecondaryInputConnection(HasOutput<InputType2>* secondary_input_connection){
        secondary_input_connection_ = secondary_input_connection;
        secondary_input_connection_->AddOutputConnection(this);
        this->Invalidate();
    }
};