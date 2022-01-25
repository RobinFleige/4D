#pragma once
#include <vtkImageActor.h>
#include <vtkImageMapper3D.h>
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkNamedColors.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include "../PipelineDefs/Renderer.h"
#include "SliderObserver.h"

class ImageRenderer : public Renderer<vtkSmartPointer<vtkImageData>>, public SliderObserver {
private:
    std::string name_ = "Test";
    vtkSmartPointer<vtkImageData> input_;
    vtkNew<vtkImageActor> actor_;
    void InternalUpdate() override;
public:
    ImageRenderer();
    void OnChange() override;
    void SetName(std::string name);
    void SetInput(vtkSmartPointer<vtkImageData> input);
};