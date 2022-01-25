#pragma once
#include <vtkCommand.h>
#include <vtkSliderRepresentation.h>
#include <vtkSliderWidget.h>
#include "SliderObserver.h"

class Slider : public vtkCommand
{
private:
    SliderObserver* observer;
    int value;
public:
    static Slider* New(){return new Slider;}
    void Execute(vtkObject *caller, unsigned long, void *);
    void Attach(SliderObserver *o, int v);
};