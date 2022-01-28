#include "ImageRenderer.h"
void ImageRenderer::InternalUpdate() {
    if(input_){
        actor_->GetMapper()->SetInputData((input_));
    }else{
        actor_->GetMapper()->SetInputData((input_connection_->GetOutput()));
    }
    window_->SetWindowName(name_.c_str());

    window_->Render();
}

ImageRenderer::ImageRenderer(){
    renderer_ = vtkSmartPointer<vtkRenderer>::New();
    window_ = vtkSmartPointer<vtkRenderWindow>::New();
    interactor_ = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    colors_ = vtkSmartPointer<vtkNamedColors>::New();

    renderer_->AddActor(actor_);
    renderer_->SetBackground(colors_->GetColor3d("SteelBlue").GetData());

    window_->SetSize(1000, 1000);
    window_->AddRenderer(renderer_);

    interactor_->SetRenderWindow(window_);
}

void ImageRenderer::OnChange(double value, int id) {
    Update();
}

void ImageRenderer::SetName(std::string name) {
    name_ = name;
    Invalidate();
}

void ImageRenderer::SetInput(vtkSmartPointer<vtkImageData> input) {
    input_ = input;
    Invalidate();
}