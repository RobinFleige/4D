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
#include <vtkLookupTable.h>
#include <vtkCellData.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkPolyDataMapper.h>
#include <vtkFlyingEdges3D.h>
#include <vtkTriangle.h>
#include <DataType/ProcessObject.h>
#include "../PipelineDefs/Renderer.h"
#include "../Slider/SliderObserver.h"
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
#include <DataType/ProcessObject.h>
#include "../PipelineDefs/Renderer.h"
#include "../Slider/SliderObserver.h"

enum RenderType {point,line,triangle};

class ImageRenderer4D : public Renderer<ProcessObject*> {
private:
    std::string name_ = "Test";
    vtkSmartPointer<vtkPolyDataMapper> mapper_;
    vtkSmartPointer<vtkActor> actor_;
    RenderType type_;
    int supportive_dimension_;
    bool use_transparency_;

    void InternalUpdate() override;
public:
    ImageRenderer4D(std::string name, RenderType type, int supportive_dimension, bool show_axes, bool use_transparency);
};