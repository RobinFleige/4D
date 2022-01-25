#pragma once
class SliderObserver {
public:
    virtual ~SliderObserver(){};
    virtual void OnChange() = 0;
};