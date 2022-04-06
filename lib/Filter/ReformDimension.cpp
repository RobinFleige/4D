#include "ReformDimension.h"

ReformDimension::ReformDimension() {
    name_ = "ReformDimension";
    Invalidate();
}

void ReformDimension::InternalUpdate() {
    output_ = new ParameterDependentVectorField(input_->GetParameterDimensions()-1, input_->GetSpaceDimensions()+1, input_->GetSize());

    std::vector<VectorField*> vector_fields;
    std::vector<Vector> vector_field_data;
    vector_fields.reserve((int)pow(output_->GetSize(),output_->GetParameterDimensions()));
    vector_field_data.reserve((int)pow(output_->GetSize(),output_->GetSpaceDimensions()));

    for(int i = 0; i < pow(output_->GetSize(),output_->GetDimensions()); i++){
        if(i%(int)pow(output_->GetSize(),output_->GetSpaceDimensions()) == 0){
            if(!vector_fields.empty()){
                vector_fields[vector_fields.size()-1]->SetData(vector_field_data);
                vector_field_data.clear();
            }
            vector_fields.push_back(new VectorField(output_->GetSpaceDimensions(),output_->GetSize()));
        }
        std::vector<int> old_ids = input_->IDsFromID(i);
        Vector vector = input_->GetData(old_ids);
        Vector fff = input_->GetFFF(old_ids,0);
        vector.values_.push_back(fff.values_[0]);
        vector_field_data.push_back(vector);
    }
    vector_fields[vector_fields.size()-1]->SetData(vector_field_data);
    output_->SetData(vector_fields);
}
