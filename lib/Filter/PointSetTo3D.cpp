#include <vector>
#include "Filter/CriticalPointsSet.h"
#include "Subspace.h"
#include "PointSetTo3D.h"


void PointSetTo3D::InternalUpdate() {
    output_.clear();
    for(int i = 0; i < size_; i++){
        vtkSmartPointer<vtkImageData> image = vtkSmartPointer<vtkImageData>::New();
        image->SetDimensions(2*size_,2*size_,2*size_);
        image->AllocateScalars(VTK_DOUBLE, 1);
        output_.push_back(image);
    }

    std::vector<int> value_ids;
    for(int i = 0; i < dimensions_; i++){
        if(i != id_){
            value_ids.push_back(i);
        }
    }

    for(int i = 0; i < input_.size(); i++){
        int image_id = input_[i]->GetCoordinates()[id_];
        std::cout<<input_[i]->GetCoordinates()[value_ids[0]]<<" "<<input_[i]->GetCoordinates()[value_ids[1]]<<" "<<input_[i]->GetCoordinates()[value_ids[2]]<<std::endl;
        auto* pixel = static_cast<double*>(output_[image_id]->GetScalarPointer(2*input_[i]->GetCoordinates()[value_ids[0]],2*input_[i]->GetCoordinates()[value_ids[1]],2*input_[i]->GetCoordinates()[value_ids[2]]));
        pixel[0] = 255;
    }
}

void PointSetTo3D::SetParameterID(int id) {
    id_ = id;
    Invalidate();
}

PointSetTo3D::PointSetTo3D(int size) {
    size_ = size;
    Invalidate();
}
