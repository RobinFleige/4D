
#include <vtkCommand.h>
#include "Slider.h"

void Slider::Execute(vtkObject* caller, unsigned long, void*)
{
    vtkSliderWidget* sliderWidget = reinterpret_cast<vtkSliderWidget*>(caller);
    double v = static_cast<vtkSliderRepresentation*>(sliderWidget->GetRepresentation())->GetValue();
    value = v;
    observer->OnChange();
}

void Slider::Attach(SliderObserver* o, int v){
    observer = o;
    value = v;
}