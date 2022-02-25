#include "TestSource.h"

TestSource::TestSource(int size) {
    size_ = size;
    step_ = (max_-min_)/size;

    Invalidate();
}

void TestSource::InternalUpdate() {
    output_ = new ProcessObject();

    auto vector_field = new VectorField4D(size_);

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
    vector_field->SetData(std::move(data));

    output_->SetVectorField(vector_field);

    std::vector<CriticalPoint*> critical_points;
    for(int s = 0; s < size_; s++){
        for(int t = 0; t < size_; t++){
            /*
            if(s>size_/2){
              critical_points.push_back({s,t,(int)abs((s-size_)/2)+(size_/2),0});
              critical_points.push_back({s,t,-(int)abs((s-size_)/2)+(size_/2),0});
            }
            if(t>size_/2){
              critical_points.push_back({s,t,(int)abs((t-size_)/2)+(size_/2),0});
              critical_points.push_back({s,t,-(int)abs((t-size_)/2)+(size_/2),0});
            }*/
            //
            if(s+t>size_){
                critical_points.push_back(new CriticalPoint({(double)s,(double)t,(double)(size_/2)+sqrt(s+t-size_),(double)size_/2}));
                critical_points.push_back(new CriticalPoint({(double)s,(double)t,(double)(size_/2)-sqrt(s+t-size_),(double)size_/2}));
            }
        }
    }
    output_->AppendCriticalPoints(critical_points);
}

double TestSource::Normalize(int i) const {
    return i*step_+min_;
}
