#include "VectorField.h"

int VectorField::IDFromIDs(std::vector<int> ids){
    int id = 0;
    for(int i = 0; i < dimensions_; i++){
        int dim_id = ids[i];
        for(int j = 0; j < i; j++){
            dim_id = dim_id*lengths_[j];
        }
        id = id+dim_id;
    }
    return id;
}

std::vector<int> VectorField::IDsFromID(int id){
    std::vector<int> ids;
    int reduced_id = id;
    ids.reserve(lengths_.size());
    for(int i = 0; i < lengths_.size(); i++){
        ids[i] = reduced_id%lengths_[i];
        reduced_id = reduced_id/lengths_[i];
    }
    return ids;
}

VectorField::VectorField(int parameter_dimensions, int space_dimensions, std::vector<int> lengths) {
    parameter_dimensions_ = parameter_dimensions;
    space_dimensions_ = space_dimensions;
    dimensions_ = parameter_dimensions+space_dimensions;
    lengths_ = lengths;

    if(dimensions_ != lengths_.size()){
        return;
    }
}

void VectorField::SetData(std::vector <SpaceVector*> vectors) {
    vectors_ = vectors;
}

std::vector<int> VectorField::GetLengths() {
    return lengths_;
}

int VectorField::GetDimensions() {
    return dimensions_;
}

int VectorField::GetParameterDimensions(){
    return parameter_dimensions_;
}

int VectorField::GetSpaceDimensions(){
    return space_dimensions_;
}

std::vector<SpaceVector *> VectorField::GetData() {
    return vectors_;
}

std::vector<double> VectorField::GetInterpolated(std::vector<double> ids) {
    for(int i = 0; i < ids.size(); i++){

    }
    return std::vector<double>();
}
