#include <Source/VectorFieldSource.h>
#include <valarray>

double VectorFieldSource::Function(std::vector<int> ids, int space_dimension){
    std::vector<double> normalized;
    for(int i = 0; i < ids.size(); i++){
        normalized.push_back(Normalize(ids[i],i));
    }
    double value;
    if(space_dimension == 0){
        value = (normalized[2]*normalized[2]+normalized[1]-1)*(normalized[3]-1)+(normalized[2]*normalized[2]+normalized[1]+1)*(normalized[3]+1);
    }else{
        value = (normalized[3]+1)*(normalized[3]-1);
    }
    if(value == 0){
        value = 0.001;
    }
    return value;
}

void VectorFieldSource::InternalUpdate(){
    output_ = new VectorField(parameter_dimensions_,space_dimensions_, widths_);
    int amount = widths_[0];
    for(int i = 1; i < parameter_dimensions_+space_dimensions_; i++){
        amount = amount * widths_[i];
    }
    std::vector<SpaceVector*> data;

    std::vector<int> ids;
    for(int i = 0; i < amount; i++){
        ids = output_->IDsFromID(i);
        std::vector<double> vector;
        for(int j = 0; j < space_dimensions_; j++){
            vector.push_back(Function(ids,j));
        }
        data.push_back(new SpaceVector(vector));
    }
    output_->SetData(data);
}

double VectorFieldSource::Normalize(int i, int parameter_id) const {
    return i*steps_[parameter_id]+mins_[parameter_id];
}

VectorFieldSource::VectorFieldSource(int parameter_dimensions, int space_dimensions, std::vector<int> widths, std::vector<double> mins, std::vector<double> maxs) {
    parameter_dimensions_ = parameter_dimensions;
    space_dimensions_ = space_dimensions;
    widths_ = widths;
    mins_ = mins;
    maxs_ = maxs;
    for(int i = 0; i < parameter_dimensions+space_dimensions; i++){
        steps_.push_back((maxs_[i]-mins_[i])/widths_[i]);
    }
    Invalidate();
}