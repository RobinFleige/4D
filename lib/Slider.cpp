
#include <vtkCommand.h>
#include "Slider.h"

void Slider::Execute(vtkObject* caller, unsigned long, void*)
{
    vtkSliderWidget* sliderWidget = reinterpret_cast<vtkSliderWidget*>(caller);
    double v = static_cast<vtkSliderRepresentation*>(sliderWidget->GetRepresentation())->GetValue();

    for(int i = 0; i < observer.size(); i++){
        observer[i]->OnChange(v,id_);
    }
}

void Slider::Attach(SliderObserver* o, int id){
    observer.push_back(o);
    id_ = id;
}