#include "ImageRenderer3D.h"
void ImageRenderer3D::InternalUpdate() {
    input_ = input_connection_->GetOutput();
    surface_->SetInputData(input_);
    surface_->Update();
    window_->SetWindowName(name_.c_str());
    window_->Render();
}

ImageRenderer3D::ImageRenderer3D(){
    renderer_ = vtkSmartPointer<vtkRenderer>::New();
    window_ = vtkSmartPointer<vtkRenderWindow>::New();
    surface_ = vtkSmartPointer<vtkFlyingEdges3D>::New();
    mapper_ = vtkSmartPointer<vtkPolyDataMapper>::New();
    actor_ = vtkSmartPointer<vtkActor>::New();
    interactor_ = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    colors_ = vtkSmartPointer<vtkNamedColors>::New();

    surface_->SetValue(0, 128);
    mapper_->SetInputConnection(surface_->GetOutputPort());
    actor_->SetMapper(mapper_);

    renderer_->AddActor(actor_);
    renderer_->SetBackground(colors_->GetColor3d("SteelBlue").GetData());


    vtkNew<vtkAxesActor> axes;
    axes->SetNormalizedShaftLength(80,80,80);
    axes->SetXAxisLabelText("S");
    axes->SetYAxisLabelText("T");
    axes->SetZAxisLabelText("X");
    axes->AxisLabelsOff();
    renderer_->AddActor(axes);

    window_->SetSize(1000, 1000);
    window_->AddRenderer(renderer_);

    interactor_->SetRenderWindow(window_);
    vtkNew<vtkInteractorStyleTrackballCamera> style;
    interactor_->SetInteractorStyle(style);
    //vtkNew<vtkInteractorStyleImage> style;
    //interactor_->SetInteractorStyle(style);
    Invalidate();
}

void ImageRenderer3D::OnChange(double value, int id) {
    Update();
}

void ImageRenderer3D::SetName(std::string name) {
    name_ = name;
    Invalidate();
}