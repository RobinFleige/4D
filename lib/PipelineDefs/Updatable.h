#pragma once
#include <string>

class Updatable{
protected:
    bool updatable_{};
    std::string name_ = "Undefined";
    virtual void InternalUpdate() = 0;

public:
    virtual void Update() = 0;
    void Invalidate(){
        updatable_ = true;
    }
};