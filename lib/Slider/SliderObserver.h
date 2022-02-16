#pragma once
class SliderObserver {
public:
    virtual void OnChange(double value, int id) = 0;
};