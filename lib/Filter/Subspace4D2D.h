#pragma once
#include <vector>
#include <vtkImageData.h>
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <Slider/SliderObserver.h>
#include "../PipelineDefs/Filter.h"
template<class T> class Subspace : public Filter<std::vector<T>,T>, public SliderObserver {
private:
    int id_;
    void InternalUpdate() override;

public:
    Subspace();
    void SetId(int id);
    void OnChange(double value, int id) override;
};


template<class T> Subspace<T>::Subspace() {
    this->Invalidate();
}

template<class T> void Subspace<T>::SetId(int id) {
    id_ = id;
    this->Invalidate();
}

template<class T> void Subspace<T>::InternalUpdate() {
    this->output_=this->input_[id_];
}

template<class T> void Subspace<T>::OnChange(double value, int id) {
    id_ = int(value);
    this->Invalidate();
    this->Update();
}