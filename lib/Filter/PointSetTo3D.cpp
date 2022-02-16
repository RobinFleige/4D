#include <vector>
#include "Filter/CriticalPointsSet.h"
#include "Subspace2D.h"
#include "PointSetTo3D.h"


void PointSetTo3D::InternalUpdate() {
    output_.clear();
    for(int i = 0; i < input_.size(); i++){
        vtkSmartPointer<vtkImageData> image = vtkSmartPointer<vtkImageData>::New();
        image->SetDimensions(input_.size(),input_.size(),input_.size());
        image->AllocateScalars(VTK_FLOAT, 1);
        output_.push_back(image);
    }

    for(int s = 0; s < input_.size(); s++){
        for(int t = 0; t < input_[0].size(); t++){
            double point[3];
            for(int i = 0; i < input_[s][t]->GetNumberOfPoints(); i++){
                input_[s][t]->GetPoint(i,point);
                if(id_ == 0){
                    auto* pixel = static_cast<float*>(output_[s]->GetScalarPointer(point[0],point[1],t));
                    pixel[0] = 255;
                }else{
                    auto* pixel = static_cast<float*>(output_[t]->GetScalarPointer(point[0],point[1],s));
                    pixel[0] = 255;
                }
            }
        }
    }
}

void PointSetTo3D::SetParameterID(int id) {
    id_ = id;
    Invalidate();
}
