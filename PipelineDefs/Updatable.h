#pragma once
class Updatable{
protected:
    bool updatable_{};
    virtual void InternalUpdate() = 0;

public:
    virtual void Update() = 0;
    void Invalidate(){
        updatable_ = true;
    }
};