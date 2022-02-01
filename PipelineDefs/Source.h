#pragma once
#include "HasOutput.h"
template<class OutputType> class Source : public HasOutput<OutputType>{
public:
    void Update() override{
        if(this->updatable_){
            this->InternalUpdate();
            for(int i = 0; i < this->output_connections_.size(); i++){
                this->output_connections_[i]->Invalidate();
            }
        }
        for(int i = 0; i < this->output_connections_.size(); i++){
            this->output_connections_[i]->Invalidate();
        }
        this->updatable_ = false;
    }
};