#pragma once
#include "HasOutput.h"
template<class OutputType> class Source : public HasOutput<OutputType>{
public:
    void Update() override{
        if(this->updatable_){
            std::cout<<"Start "<<this->name_<<std::endl;
            this->InternalUpdate();
            std::cout<<"End "<<this->name_<<std::endl;
            this->updatable_ = false;
            for(int i = 0; i < this->output_connections_.size(); i++){
                this->output_connections_[i]->Invalidate();
            }
        }
    }
};