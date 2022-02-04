#pragma once
#include "HasInput.h"
#include "HasSecondaryInput.h"
#include "Renderer.h"

template<class InputType1, class InputType2> class DoubleRenderer : public HasSecondaryInput<InputType1, InputType2>{
protected:
    vtkSmartPointer<vtkRenderer> renderer_;
    vtkSmartPointer<vtkRenderWindow> window_;
    vtkSmartPointer<vtkRenderWindowInteractor> interactor_;
    vtkSmartPointer<vtkNamedColors> colors_;

public:
    void Update() override{
        if(this->input_connection_){
            this->input_connection_->Update();
            this->input_ = this->input_connection_->GetOutput();
        }
        if(this->secondary_input_connection_){
            this->secondary_input_connection_->Update();
            this->secondary_input_ = this->secondary_input_connection_->GetOutput();
        }
        if(this->updatable_){
            this->InternalUpdate();
            this->updatable_ = false;
        }
    }

    vtkSmartPointer<vtkRenderWindowInteractor> GetInteractor(){
        return interactor_;
    }
};