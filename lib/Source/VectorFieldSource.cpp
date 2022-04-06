#include <Source/VectorFieldSource.h>
#include <valarray>

void VectorFieldSource::InternalUpdate(){
    output_ = new ParameterDependentVectorField(parameter_dimensions_, space_dimensions_, size_);
    std::vector<VectorField*> fields;
    fields.reserve(pow(size_,parameter_dimensions_));
    for(int p = 0; p < pow(size_,parameter_dimensions_); p++){
        std::vector<int> parameter_ids = output_->ParameterIDsFromID(p);
        std::vector<Vector> vectors;
        vectors.reserve(pow(size_,space_dimensions_));
        for(int d = 0; d < pow(size_,space_dimensions_); d++){
            std::vector<int> space_ids = output_->SpaceIDsFromID(d);
            std::vector<int> ids = parameter_ids;
            for(int d2 = 0; d2 < space_dimensions_; d2++){
                ids.push_back(space_ids[d2]);
            }
            std::vector<double> vector;
            if(type_ == VectorFieldExampleType::simple2d2d){
                vector.reserve(2);
                vector.push_back(Normalize(ids[2])*Normalize(ids[2])-Normalize(ids[0])-Normalize(ids[1]));
                vector.push_back(Normalize(ids[3])+Normalize(ids[0]));
            }
            if(type_ == VectorFieldExampleType::double2d2d){
                vector.reserve(2);
                vector.push_back((Normalize(ids[2])*Normalize(ids[2])+Normalize(ids[1]))*((Normalize(ids[3])-1))-(Normalize(ids[2])*Normalize(ids[2])+Normalize(ids[0]))*((Normalize(ids[3])+1)));
                vector.push_back(((Normalize(ids[3])-1))*((Normalize(ids[3])+1)));
            }
            if(type_ == VectorFieldExampleType::circle2d2d){
                vector.reserve(2);
                vector.push_back(Normalize(ids[2])*Normalize(ids[2])+Normalize(ids[1])*Normalize(ids[1])+Normalize(ids[0])*Normalize(ids[0])-1);
                vector.push_back(Normalize(ids[3]));
            }
            if(type_ == VectorFieldExampleType::simple2d2d_without_y){
                vector.reserve(2);
                vector.push_back(Normalize(ids[2])*Normalize(ids[2])-Normalize(ids[0])-Normalize(ids[1]));
                vector.push_back(Normalize(ids[3]));
            }
            if(type_ == VectorFieldExampleType::simple2d3d){
                vector.reserve(3);
                vector.push_back(Normalize(ids[2])*Normalize(ids[2])-Normalize(ids[0])-Normalize(ids[1]));
                vector.push_back(Normalize(ids[3]));
                vector.push_back(Normalize(ids[4]));
            }
            if(type_ == VectorFieldExampleType::simple3d2d){
                vector.reserve(2);
                vector.push_back(Normalize(ids[3])*Normalize(ids[3])-Normalize(ids[0])-Normalize(ids[1])-Normalize(ids[2]));
                vector.push_back(Normalize(ids[4]));
            }
            if(type_ == VectorFieldExampleType::circle3d2d){
                vector.reserve(2);
                vector.push_back(Normalize(ids[3])*Normalize(ids[3])+Normalize(ids[2])*Normalize(ids[2])+Normalize(ids[1])*Normalize(ids[1])+Normalize(ids[0])*Normalize(ids[0])-1);
                vector.push_back(Normalize(ids[4]));
            }
            auto vec = new Vector();
            vec->values_ = vector;
            vectors.push_back(*vec);
        }
        auto vectorField = new VectorField(2,size_);
        vectorField->SetData(vectors);
        fields.push_back(vectorField);
    }
    output_->SetData(std::move(fields));
}

double VectorFieldSource::Normalize(int i) const {
    return i*step_+min_;
}

VectorFieldSource::VectorFieldSource(int size, double min, double max, VectorFieldExampleType type) {
    name_ = "VectorFieldSource";
    size_ = size;
    min_= min;
    max_ = max;
    step_ = (max_-min_)/size;
    type_ = type;

    if(type_ == VectorFieldExampleType::simple2d2d || type_ == VectorFieldExampleType::double2d2d || type_ == VectorFieldExampleType::circle2d2d || type_ == VectorFieldExampleType::simple2d2d_without_y){
        parameter_dimensions_ = 2;
        space_dimensions_ = 2;
    }
    if(type_ == VectorFieldExampleType::simple2d3d){
        parameter_dimensions_ = 2;
        space_dimensions_ = 3;
    }
    if(type_ == VectorFieldExampleType::simple3d2d || type_ == VectorFieldExampleType::circle3d2d){
        parameter_dimensions_ = 3;
        space_dimensions_ = 2;
    }

    Invalidate();
}