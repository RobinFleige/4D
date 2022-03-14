#include "ImageRenderer2D.h"
void ImageRenderer2D::InternalUpdate() {
    input_ = input_connection_->GetOutput();
    actor_->GetMapper()->SetInputData((input_));
    window_->SetWindowName(window_name_.c_str());
    window_->Render();
}

ImageRenderer2D::ImageRenderer2D(){
    name_ = "ImageRenderer2D";
    renderer_ = vtkSmartPointer<vtkRenderer>::New();
    window_ = vtkSmartPointer<vtkRenderWindow>::New();
    interactor_ = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    colors_ = vtkSmartPointer<vtkNamedColors>::New();

    renderer_->AddActor(actor_);
    renderer_->SetBackground(colors_->GetColor3d("SteelBlue").GetData());

    window_->SetSize(1000, 1000);
    window_->AddRenderer(renderer_);

    interactor_->SetRenderWindow(window_);
    vtkNew<vtkInteractorStyleImage> style;
    interactor_->SetInteractorStyle(style);
    Invalidate();
}

void ImageRenderer2D::OnChange(double value, int id) {
    Update();
}

void ImageRenderer2D::SetName(std::string name) {
    window_name_ = name;
    Invalidate();
}