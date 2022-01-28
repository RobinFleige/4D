#pragma once
#include "Updatable.h"
#include <vector>

template<class OutputType> class HasOutput : public Updatable{
protected:
    OutputType output_;
    std::vector<Updatable*> output_connections_;

public:
    OutputType GetOutput(){
        if(updatable_){
            Update();
        }
        return output_;
    }
    void AddOutputConnection(Updatable* output_connection){
        output_connections_.push_back(output_connection);
    }
};