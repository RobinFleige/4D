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