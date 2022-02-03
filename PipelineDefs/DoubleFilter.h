#pragma once
#include "HasInput.h"
#include "HasOutput.h"
template<class InputType1, class InputType2, class OutputType> class DoubleFilter : public HasInput<InputType1>, public HasOutput<OutputType>{
protected:
    HasOutput<InputType2>* secondary_input_connection_;
    InputType2 secondary_input_;
public:
    void SetSecondaryInputConnection(HasOutput<InputType2>* secondary_input_connection){
        secondary_input_connection_ = secondary_input_connection;
        secondary_input_connection_->AddOutputConnection(this);
        this->Invalidate();
    }
    void Update() override{
        if(this->input_connection_){
            this->input_connection_->Update();
            this->input_ = this->input_connection_->GetOutput();
        }
        if(this->secondary_input_connection_){
            this->secondary_input_connection_->Update();
            this->secondary_input_ = this->secondary_input_connection_->GetOutput();
        }
        if(this->updatable_){
            this->InternalUpdate();
            this->updatable_ = false;
            for(int i = 0; i < this->output_connections_.size(); i++){
                this->output_connections_[i]->Invalidate();
            }
        }
    }
};