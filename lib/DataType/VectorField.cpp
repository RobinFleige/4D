#include <valarray>
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
    for(int i = 0; i < lengths_.size(); i++){
        ids.push_back(reduced_id%lengths_[i]);
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
    std::vector<std::vector<int>> ids_set;
    for(int j = 0; j < pow(2,ids.size()); j++){
        std::vector<int> next_ids;
        for(int k = 0; k < ids.size(); k++){
            int next_id = floor(ids[k]);
            if(j%((int)pow(2,k+1)) >= pow(2,k)){
                next_id = next_id+1;
            }
            next_ids.push_back(next_id);
        }
        ids_set.push_back(next_ids);
    }

    std::vector<double> values;
    for(int i = 0; i < GetParameterDimensions(); i++){
        values.push_back(0);
    }
    for(int i = 0; i < ids_set.size(); i++){
        std::vector<double> value = *GetData()[IDFromIDs(ids_set[i])]->GetValues();
        double multiplicator = 1;
        for(int j = 0; j < ids_set[i].size(); j++){
            if(ids_set[i][j] > ids[j]){
                multiplicator = multiplicator * (1-(ids_set[i][j]-ids[j]));
            }else{
                multiplicator = multiplicator * (1-(ids[j]-ids_set[i][j]));
            }
        }
        for(int j = 0; j < GetParameterDimensions(); j++){
            values[j] = values[j]+value[j]*multiplicator;
        }
    }
    return values;
}
