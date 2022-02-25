#include <Source/VectorFieldSource.h>
#include <valarray>

double VectorFieldSource::Function(std::vector<int> ids, int space_dimension){
    std::vector<double> normalized;
    for(int i = 0; i < ids.size(); i++){
        normalized.push_back(Normalize(i));
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
    output_ = new VectorField4D(size_);

    std::vector<std::vector<std::vector<std::vector<std::vector<double>>>>> data;
    data.reserve(size_);
    for(int s = 0; s < size_; s++){
        std::vector<std::vector<std::vector<std::vector<double>>>> txy_vector;
        txy_vector.reserve(size_);
        for(int t = 0; t < size_; t++){
            std::vector<std::vector<std::vector<double>>> xy_vector;
            xy_vector.reserve(size_);
            for(int x = 0; x < size_; x++){
                std::vector<std::vector<double>> y_vector;
                y_vector.reserve(size_);
                for(int y = 0; y < size_; y++){
                    std::vector<double> vector;
                    vector.reserve(2);
                    vector.push_back(Normalize(x)*Normalize(x)-Normalize(s)-Normalize(t));
                    vector.push_back(Normalize(y));
                    y_vector.push_back(vector);
                }
                xy_vector.push_back(std::move(y_vector));
            }
            txy_vector.push_back(std::move(xy_vector));
        }
        data.push_back(std::move(txy_vector));
    }
    output_->SetData(std::move(data));
}

double VectorFieldSource::Normalize(int i) const {
    return i*step_+min_;
}

VectorFieldSource::VectorFieldSource(int size, double min, double max) {
    size_ = size;
    min_= min;
    max_ = max;
    step_ = (max_-min_)/size;
    Invalidate();
}