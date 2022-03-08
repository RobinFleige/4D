#pragma once
#include <vtkImageActor.h>
#include <vtkImageMapper3D.h>
#include <vtkSmartPointer.h>
#include <vtkAxesActor.h>
#include <vtkLine.h>
#include <vtkImageData.h>
#include <vtkProperty.h>
#include <vtkNamedColors.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkPolyDataMapper.h>
#include <vtkFlyingEdges3D.h>
#include <DataType/ProcessObject.h>
#include "../PipelineDefs/Renderer.h"
#include "../Slider/SliderObserver.h"

class CriticalPointRenderer3D : public Renderer<ProcessObject*>, public SliderObserver {
private:
    std::string name_ = "Test";
    vtkSmartPointer<vtkPolyDataMapper> mapper_;
    vtkSmartPointer<vtkActor> actor_;
    void InternalUpdate() override;
public:
    CriticalPointRenderer3D();
    void OnChange(double value, int id) override;
    void SetName(std::string name);
};