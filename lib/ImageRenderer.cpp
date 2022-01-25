#include "ImageRenderer.h"
void ImageRenderer::InternalUpdate() {
    if(input_){
        actor_->GetMapper()->SetInputData((input_));
    }else{
        actor_->GetMapper()->SetInputData((input_connection_->GetOutput()));
    }

    window_->Render();
    interactor_->Start();
}

ImageRenderer::ImageRenderer(){
    renderer_->AddActor(actor_);
    renderer_->SetBackground(colors_->GetColor3d("SteelBlue").GetData());

    window_->SetSize(1000, 1000);
    window_->AddRenderer(renderer_);
    window_->SetWindowName(name_.c_str());

    interactor_->SetRenderWindow(window_);
}

void ImageRenderer::OnChange() {
    Update();
}

void ImageRenderer::SetName(std::string name) {
    name_ = name;
}

void ImageRenderer::SetInput(vtkSmartPointer<vtkImageData> input) {
    input_ = input;
}