#include <utility>
#include <valarray>
#include <iostream>
#include "ParameterDependentVectorField.h"

VectorField* ParameterDependentVectorField::GetVectorField(std::vector<int> ids) {
    return vector_fields[IDFromIDs(ids)];
}

Vector ParameterDependentVectorField::GetData(std::vector<int> ids) {
    std::vector<int> primary_ids;
    std::vector<int> secondary_ids;
    for(int i = 0; i < ids.size(); i++){
        if(i < parameter_dimensions_){
            primary_ids.push_back(ids[i]);
        }else{
            secondary_ids.push_back(ids[i]);
        }
    }
    return GetVectorField(primary_ids)->GetData(secondary_ids);
}

ParameterDependentVectorField::ParameterDependentVectorField(int parameter_dimensions, int space_dimensions, int size) {
    parameter_dimensions_ = parameter_dimensions;
    space_dimensions_ = space_dimensions;
    size_ = size;
}

void ParameterDependentVectorField::SetData(std::vector<VectorField*> values) {
    vector_fields = std::move(values);
}

int ParameterDependentVectorField::GetSize() {
    return size_;
}

Vector ParameterDependentVectorField::GetInterpolated(std::vector<double> ids) {
    int points_count = pow(2,parameter_dimensions_+space_dimensions_);
    std::vector<double> factors;
    factors.reserve(points_count);
    std::vector<std::vector<int>> id_set;
    id_set.reserve(points_count);

    for(int i = 0; i < points_count; i++){
        double factor = 1;
        std::vector<int> rounded_ids;
        rounded_ids.reserve(parameter_dimensions_+space_dimensions_);

        for(int j = 0; j < parameter_dimensions_+space_dimensions_; j++){
            if(i%((int)pow(2,j+1)) < (int)pow(2,j)){
                factor*=(floor(ids[j])-ids[j]+1);
                rounded_ids.push_back(floor(ids[j]));
            }else{
                factor*=(ids[j]-floor(ids[j]));
                rounded_ids.push_back(ceil(ids[j]));
            }
        }

        factors.push_back(factor);
        id_set.push_back(rounded_ids);
    }

    std::vector<double> values;
    values.reserve(space_dimensions_);
    for(int i = 0; i < space_dimensions_; i++){
        values.push_back(0);
    }

    for(int i = 0; i < points_count; i++){
        for(int d = 0; d < space_dimensions_; d++){
            values[d]+=factors[i]*GetData(id_set[i]).values_[d];
        }
    }

    auto vec = new Vector();
    vec->values_ = values;

    return *vec;
}

void ParameterDependentVectorField::SetFeatureFlowField(std::vector<VectorField*> fffs) {
    fffs_ = std::move(fffs);
}

Vector ParameterDependentVectorField::GetFFF(std::vector<int> ids, int d) {
    return fffs_[d]->GetData(ids);
}

Vector ParameterDependentVectorField::GetInterpolatedFFF(std::vector<double> ids, int d) {
    return fffs_[d]->GetInterpolated(ids);
}

int ParameterDependentVectorField::IDFromIDs(std::vector<int> ids) {
    int id = 0;
    for(int i = 0; i < parameter_dimensions_; i++){
        id+=ids[i]*(int)pow(size_,parameter_dimensions_-i-1);
    }
    return id;
}

std::vector<int> ParameterDependentVectorField::IDsFromID(int id) {
    std::vector<int> ids;
    ids.reserve(parameter_dimensions_);
    for(int i = 0; i < parameter_dimensions_; i++){
        ids.push_back(id%(int)pow(size_,parameter_dimensions_-i)/(int)pow(size_,parameter_dimensions_-i-1));
    }
    return ids;
}

int ParameterDependentVectorField::GetDimensions() {
    return parameter_dimensions_+space_dimensions_;
}

int ParameterDependentVectorField::GetParameterDimensions() {
    return parameter_dimensions_;
}

int ParameterDependentVectorField::IDFromIDsFull(std::vector<int> ids) {
    int id = 0;
    for(int i = 0; i < GetDimensions(); i++){
        id+=ids[i]*(int)pow(size_,GetDimensions()-i-1);
    }
    return id;
}

std::vector<int> ParameterDependentVectorField::IDsFromIDFull(int id) {
    std::vector<int> ids;
    ids.reserve(GetDimensions());
    for(int i = 0; i < GetDimensions(); i++){
        ids.push_back(id%(int)pow(size_,GetDimensions()-i)/(int)pow(size_,GetDimensions()-i-1));
    }
    return ids;
}

int ParameterDependentVectorField::GetSpaceDimensions() {
    return space_dimensions_;
}
