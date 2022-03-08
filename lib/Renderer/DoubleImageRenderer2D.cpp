#include "DoubleImageRenderer2D.h"

void DoubleImageRenderer2D::InternalUpdate() {
    input_ = input_connection_->GetOutput();
    secondary_input_ = secondary_input_connection_->GetOutput();
    actor_->GetMapper()->SetInputData((input_));
    secondary_actor_->GetMapper()->SetInputData((secondary_input_));
    window_->SetWindowName(name_.c_str());
    window_->Render();

}

DoubleImageRenderer2D::DoubleImageRenderer2D() {
    renderer_ = vtkSmartPointer<vtkRenderer>::New();
    window_ = vtkSmartPointer<vtkRenderWindow>::New();
    interactor_ = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    colors_ = vtkSmartPointer<vtkNamedColors>::New();

    actor_->SetPosition(-100,0,0);
    actor_->SetPosition(100,0,0);
    renderer_->AddActor(actor_);
    renderer_->AddActor(secondary_actor_);
    renderer_->SetBackground(colors_->GetColor3d("SteelBlue").GetData());

    window_->SetSize(1000, 1000);
    window_->AddRenderer(renderer_);

    interactor_->SetRenderWindow(window_);
    vtkNew<vtkInteractorStyleImage> style;
    interactor_->SetInteractorStyle(style);
    Invalidate();

}

void DoubleImageRenderer2D::OnChange(double value, int id) {
    Update();
}

void DoubleImageRenderer2D::SetName(std::string name) {
    name_ = name;
    Invalidate();
}
