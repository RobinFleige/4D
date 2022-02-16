#pragma once
#include <vtkImageActor.h>
#include <vtkImageMapper3D.h>
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkNamedColors.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include "../../PipelineDefs/DoubleRenderer.h"
#include "Source/Slider/SliderObserver.h"

class DoubleImageRenderer : public DoubleRenderer<vtkSmartPointer<vtkImageData>,vtkSmartPointer<vtkImageData>>, public SliderObserver{
private:
    std::string name_ = "Test";
    vtkNew<vtkImageActor> actor_;
    vtkNew<vtkImageActor> secondary_actor_;
    void InternalUpdate() override;
public:
    DoubleImageRenderer();
    void OnChange(double value, int id) override;
    void SetName(std::string name);
};