#pragma once
#include "HasInput.h"
#include "HasSecondaryInput.h"
#include "HasOutput.h"
template<class InputType1, class InputType2, class OutputType> class DoubleFilter : public HasSecondaryInput<InputType1,InputType2>, public HasOutput<OutputType>{
public:
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
            std::cout<<"Start "<<typeid(this).name()<<std::endl;
            this->InternalUpdate();
            std::cout<<"End "<<typeid(this).name()<<std::endl;
            this->updatable_ = false;
            for(int i = 0; i < this->output_connections_.size(); i++){
                this->output_connections_[i]->Invalidate();
            }
        }
    }
};