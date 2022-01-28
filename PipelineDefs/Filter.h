#pragma once
#include "HasInput.h"
#include "HasOutput.h"
template<class InputType, class OutputType> class Filter : public HasInput<InputType>, public HasOutput<OutputType>{
public:
    void Update() override{
        if(this->input_connection_){
            this->input_connection_->Update();
            this->input_ = this->input_connection_->GetOutput();
        }
        if(this->updatable_){
            this->InternalUpdate();
            for(int i = 0; i < this->output_connections_.size(); i++){
                this->output_connections_[i]->Invalidate();
            }
        }
        for(int i = 0; i < this->output_connections_.size(); i++){
            this->output_connections_[i]->Update();
        }
    }
};