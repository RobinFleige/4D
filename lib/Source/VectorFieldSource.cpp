#include <Source/VectorFieldSource.h>
#include <valarray>

void VectorFieldSource::InternalUpdate(){
    output_ = new ProcessObject();
    auto temp = new ParameterDependentVectorField(size_);

    std::vector<std::vector<VectorField*>> data;
    data.reserve(size_);
    for(int s = 0; s < size_; s++){
        std::vector<VectorField*> txy_vector;
        txy_vector.reserve(size_);
        for(int t = 0; t < size_; t++){
            std::vector<Vector> xy_vector;
            xy_vector.reserve(size_*size_);
            for(int x = 0; x < size_; x++){
                for(int y = 0; y < size_; y++){
                    std::vector<double> vector;
                    vector.reserve(2);
                    if(type_ == VectorFieldExampleType::simple4d){
                        vector.push_back(Normalize(x)*Normalize(x)-Normalize(s)-Normalize(t));
                        vector.push_back(Normalize(y)+Normalize(s));
                    }
                    if(type_ == VectorFieldExampleType::double4d){
                        vector.push_back((Normalize(x)*Normalize(x)+Normalize(t))*((Normalize(y)-1))-(Normalize(x)*Normalize(x)+Normalize(s))*((Normalize(y)+1)));
                        vector.push_back(((Normalize(y)-1))*((Normalize(y)+1)));
                    }
                    if(type_ == VectorFieldExampleType::circle4d){
                        vector.push_back(Normalize(x)*Normalize(x)+Normalize(t)*Normalize(t)+Normalize(s)*Normalize(s)-1);
                        vector.push_back(Normalize(y));
                    }
                    if(type_ == VectorFieldExampleType::simple4d_without_y){
                        vector.push_back(Normalize(x)*Normalize(x)-Normalize(s)-Normalize(t));
                        vector.push_back(Normalize(y));
                    }
                    if(type_ == VectorFieldExampleType::simple5d){
                        vector.push_back(Normalize(x)*Normalize(x)-Normalize(s)-Normalize(t));
                        vector.push_back(Normalize(y));
                    }
                    auto vec = new Vector();
                    vec->values_ = vector;
                    xy_vector.push_back(*vec);
                }
            }
            auto vectorField = new VectorField(2,size_);
            vectorField->SetData(xy_vector);
            txy_vector.push_back(vectorField);
        }
        data.push_back(std::move(txy_vector));
    }
    temp->SetData(std::move(data));
    output_->SetVectorField(temp);
}

double VectorFieldSource::Normalize(int i) const {
    return i*step_+min_;
}

VectorFieldSource::VectorFieldSource(int size, double min, double max, VectorFieldExampleType type) {
    size_ = size;
    min_= min;
    max_ = max;
    step_ = (max_-min_)/size;
    type_ = type;
    Invalidate();
}