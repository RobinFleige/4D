#pragma once
#include "HasInput.h"
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkNamedColors.h>

template<class InputType> class Renderer : public HasInput<InputType>{
protected:
    std::string window_name_ = "Test";
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
        if(this->updatable_){
            std::cout<<"Start "<<this->name_<<std::endl;
            this->InternalUpdate();
            std::cout<<"End "<<this->name_<<std::endl;
            this->updatable_ = false;
        }
    }

    vtkSmartPointer<vtkRenderWindowInteractor> GetInteractor(){
        return interactor_;
    }
};