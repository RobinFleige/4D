#include "PointSource.h"

void PointSource::SetX(int x) {
    x_ = x;
    Invalidate();
}

void PointSource::SetY(int y) {
    y_ = y;
    Invalidate();
}

void PointSource::InternalUpdate() {
    output_ = vtkSmartPointer<vtkPoints>::New();
    output_->InsertNextPoint(x_,y_,0);
}

PointSource::PointSource() {
    Invalidate();
}


void PointSource::OnChange(double value, int id) {
    if(id == 0){
        x_ = value;
    }else if(id == 1){
        y_ = value;
    }
    Invalidate();
}