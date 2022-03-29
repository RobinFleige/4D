#include "VectorField.h"

VectorField::VectorField(int dimensions, int size) {
    dimensions_ = dimensions;
    size_ = size;
}

void VectorField::SetData(std::vector<Vector> vectors) {
    vectors_ = std::move(vectors);
}

int VectorField::GetSize() const {
    return size_;
}

Vector VectorField::GetData(std::vector<int> ids) {
    int id = IDFromIDs(ids);
    return vectors_[id];
}

Vector VectorField::GetInterpolated(std::vector<double> ids) {
    int points_count = pow(2,dimensions_);
    std::vector<double> factors;
    factors.reserve(points_count);
    std::vector<std::vector<int>> id_set;
    id_set.reserve(points_count);

    for(int i = 0; i < points_count; i++){
        double factor = 1;
        std::vector<int> rounded_ids;
        rounded_ids.reserve(dimensions_);

        for(int j = 0; j < dimensions_; j++){
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
    values.reserve(dimensions_);
    for(int i = 0; i < dimensions_; i++){
        values.push_back(0);
    }

    for(int i = 0; i < points_count; i++){
        for(int d = 0; d < dimensions_; d++){
            values[d]+=factors[i]*GetData(id_set[i]).values_[d];
        }
    }

    auto vec = new Vector();
    vec->values_ = values;

    return *vec;
}

int VectorField::IDFromIDs(std::vector<int> ids) {
    int id = 0;
    for(int i = 0; i < dimensions_; i++){
        id+=ids[i]*(int)pow(size_,dimensions_-i-1);
    }
    return id;
}

std::vector<int> VectorField::IDsFromID(int id) {
    std::vector<int> ids;
    ids.reserve(dimensions_);
    for(int i = 0; i < dimensions_; i++){
        ids.push_back(id%(int)pow(size_,dimensions_-i)/(int)pow(size_,dimensions_-i-1));
    }
    if(ids.size() == 0){
        ids.push_back(0);
    }
    return ids;
}
