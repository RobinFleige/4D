#pragma once
#include <vtkImageActor.h>
#include <vtkImageMapper3D.h>
#include <vtkSmartPointer.h>
#include <vtkAxesActor.h>
#include <vtkImageData.h>
#include <vtkNamedColors.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkPolyDataMapper.h>
#include <vtkFlyingEdges3D.h>
#include "../PipelineDefs/Renderer.h"
#include "../Slider/SliderObserver.h"

class ImageRenderer3D : public Renderer<vtkSmartPointer<vtkImageData>>, public SliderObserver {
private:
    vtkSmartPointer<vtkFlyingEdges3D> surface_;
    vtkSmartPointer<vtkPolyDataMapper> mapper_;
    vtkSmartPointer<vtkActor> actor_;
    void InternalUpdate() override;
public:
    ImageRenderer3D();
    void OnChange(double value, int id) override;
    void SetName(std::string name);
};