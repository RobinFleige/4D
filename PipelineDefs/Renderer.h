#pragma once
#include <vtkSmartPointer.h>
#include "HasOutput.h"

template<class T> class Renderer{
protected:
    virtual ~Renderer(){};
    vtkNew<vtkNamedColors> colors_;
    vtkNew<vtkRenderer> renderer_;
    vtkNew<vtkRenderWindow> window_;
    vtkNew<vtkRenderWindowInteractor> interactor_;

    bool updatable_ = true;
    HasOutput<T>* input_connection_;

    virtual void InternalUpdate() = 0;
public:
    vtkSmartPointer<vtkRenderWindowInteractor> GetInteractor() { return interactor_; }

    virtual void SetInputConnection(HasOutput<T>* input_connection){
        input_connection_ = input_connection;
        updatable_ = true;
    }

    virtual void Update(){
        if(input_connection_){
            input_connection_->Update();
        }
        if(updatable_){
            InternalUpdate();
            updatable_ = false;
        }
    }
};