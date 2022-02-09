#include "MultiparameterDependentStructuredGridnD.h"

MultiparameterDependentStructuredGridnD::MultiparameterDependentStructuredGridnD(int field_dimensions,
                                                                                 int vector_dimension,
                                                                                 std::vector<double> mins,
                                                                                 std::vector<double> maxs,
                                                                                 std::vector<int> lengths,
                                                                                 int function_id) {
    field_dimensions_ = field_dimensions;
    vector_dimension_ = vector_dimension;
    mins_ = mins;
    maxs_ = maxs;
    lengths_ = lengths;

    if(field_dimensions_ != mins_.size() || field_dimensions_ != maxs_.size() || field_dimensions_ != lengths_.size()){
        return;
    }

    for(int i = 0; i < field_dimensions; i++){
        steps_.push_back((maxs_[i]-mins_[i])/lengths_[i]);
    }

    int amount = lengths[0];
    for(int i = 1; i < field_dimensions; i++){
        amount = amount * lengths[i];
    }
    amount_ = amount;

    GenerateData(function_id);
}

void MultiparameterDependentStructuredGridnD::GenerateData(int id) {
    data_.clear();
    data_.reserve(amount_);
    std::vector<int> ids_;
    for(int i = 0; i < amount_; i++){
        ids = GetIds(i);
        std::vector<double> vector;
        for(int j = 0; j < vector_dimension_; j++){
            vector.push_back(ParameterFunction(ids,j));
        }
        data_[i] = vector;
    }
}

float MultiparameterDependentStructuredGridnD::ParameterFunction(std::vector<int> ids, int dimension){
    std::vector<double> normalized;
    for(int i = 0; i < ids.size(); i++){
        normalized.push_back(Normalize(ids[i],i))
    }

    if(dimension == 0){
        return (normalized[0]*normalized[0]+normalized[3]-1)*(normalized[1]-1)+(normalized[0]*normalized[0]+normalized[3]+1)*(normalized[1]+1);
    }else{
        return (normalized[1]+1)*(normalized[1]-1);
    }
}

int MultiparameterDependentStructuredGridnD::GetId(std::vector<int> ids){
    int id = 0;
    for(int i = 0; i < field_dimensions; i++){
        int dim_id = ids[i]
        for(int j = 0; j < i; j++){
            dim_id = dim_id*lengths_[j];
        }
        id = id+dim_id;
    }
    return id;
}

std::vector<int> MultiparameterDependentStructuredGridnD::GetIds(int id){
    std::vector<int> ids;
    int reduced_id = id;
    ids.reserve(lengths_.size());
    for(int i = 0; i < lengths_.size(); i++){
        ids[i] = reduced_id%lengths_[i];
        reduced_id = reduced_id/lengths_[i];
    }
    return ids;
}

double MultiparameterDependentStructuredGridnD::Normalize(int i, int parameter_id) const {
    return i*steps_[parameter_id]+min_[parameter_id];
}

std::vector<int> MultiparameterDependentStructuredGridnD::GetCriticalPoints(){
    std::vector<std::vector<int>> critical_points;
    for(int i = 0; i < amount_; i++){
        std::vector<int> ids = GetIds(i);
        int changed_dimensions = 0;
        //For every dimension -> Check for value change
        for(int j = 0; j < vector_dimension_; j++){
            bool changed = false;
            //If most left also check if left == 0
            if(ids[j] == 0){
                //Check for links == 0
                if(data_[i][j] == 0){
                    changed = true;
                }
            }
            //Check for rechts == 0
            std::vector<int> next_ids = ids;
            next_ids[j] = next_ids[j]+1;
            if(data_[GetId(next_ids)][j] == 0){
                changed = true;
            }
            //Check Vorzeichenwechsel oder rechts == 0
            if(data_[GetId(next_ids)][j]*data_[i][j] < 0){
                changed = true;
            }

            if(changed){
                changed_dimensions++;
            }
        }
        if(changed_dimensions == vector_dimension_){
            critical_points.push_back(i);
        }
    }
}

std::vector<std::vector<double> MultiparameterDependentStructuredGridnD::GetExactCriticalPoints(std::vector<std::vector<int> critical_points){

}