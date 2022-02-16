#pragma once
#include <vtkCommand.h>
#include <vtkSliderRepresentation.h>
#include <vtkSliderWidget.h>
#include "SliderObserver.h"

class Slider : public vtkCommand
{
private:
    std::vector<SliderObserver*> observer;
    int id_;
public:
    static Slider* New(){return new Slider;}
    void Execute(vtkObject *caller, unsigned long, void *) override;
    void Attach(SliderObserver *o, int id);
};