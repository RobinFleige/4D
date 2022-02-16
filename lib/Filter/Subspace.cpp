#include "Subspace.h"

void Subspace::SetParameters(std::vector<int> parameters) {
    parameters_ = parameters;
    Invalidate();
}

void Subspace::InternalUpdate() {
    input_ = input_connection_->GetOutput();
    std::vector<int> begin_ids = parameters_;
    std::vector<int> end_ids = parameters_;
    std::vector<int> new_lengths;
    for(int i = begin_ids.size(); i < input_->GetDimensions(); i++){
        begin_ids.push_back(0);
        end_ids.push_back(input_->GetLengths()[i]);
        new_lengths.push_back(input_->GetLengths()[i]);
    }
    int begin_id = input_->IDFromIDs(begin_ids);
    int end_id = input_->IDFromIDs(end_ids);
    auto first = input_->GetData().begin()+begin_id;
    auto last = input_->GetData().begin()+end_id;
    std::vector<SpaceVector*> new_data(first,last);
    output_ = new VectorField(input_->GetParameterDimensions()-parameters_.size(),input_->GetSpaceDimensions(),new_lengths);
    output_->SetData(new_data);

}



void Subspace::OnChange(double value, int id) {
    if(id == 0){
        parameters_[id] = value;
    }
    Invalidate();
    Update();
}

Subspace::Subspace() {
    Invalidate();
}


