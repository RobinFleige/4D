#include "CalculateFFField.h"

CalculateFFField::CalculateFFField() {
    name_ = "CalculateFFField";
    Invalidate();
}

void CalculateFFField::InternalUpdate() {
    output_ = input_;
    int size = input_->GetSize();

    std::vector<VectorField*> fffs;
    fffs.reserve(input_->GetParameterDimensions());
    std::vector<std::vector<Vector>> fff_vectors;
    fff_vectors.reserve(input_->GetParameterDimensions());

    for(int d = 0; d < input_->GetParameterDimensions(); d++){
        std::vector<Vector> fff_vector;
        fff_vector.reserve((int)pow(size,input_->GetDimensions()));
        fff_vectors.push_back(fff_vector);
    }

    for(int i = 0; i < (int)pow(size,input_->GetDimensions()); i++){

        if(i%1000==0){
            std::cout<<i<<std::endl;
        }

        std::vector<Vector> derivatives;
        std::vector<int> ids = input_->IDsFromID(i);

        for(int d = 0; d < input_->GetDimensions(); d++){
            Vector prev;
            Vector next;
            double factor = 1;
            std::vector<int> prev_ids = ids;
            std::vector<int> next_ids = ids;
            if(ids[d] == 0){
                prev_ids[d] = 0;
                factor = 2;
            }else{
                prev_ids[d] = ids[d]-1;
            }
            prev = input_->GetData(prev_ids);
            if(ids[d] == input_->GetSize()-1){
                next_ids[d] = input_->GetSize()-1;
                factor = 2;
            }else{
                next_ids[d] = ids[d]+1;
            }
            next = input_->GetData(next_ids);
            derivatives.push_back(Vector::Derivative(next,prev,factor));
        }

        for(int d = 0; d < input_->GetParameterDimensions(); d++){
            std::vector<double> fff;

            std::vector<int> ids;
            for(int d2 = 0; d2 < input_->GetSpaceDimensions()*2+input_->GetParameterDimensions()-1; d2++){
                if(d2==input_->GetSpaceDimensions()){
                    ids.push_back(d);
                    d2+=input_->GetParameterDimensions()-1;
                }else{
                    ids.push_back(d2+input_->GetParameterDimensions());
                }
            }

            for(int d2 = 0; d2< input_->GetParameterDimensions(); d2++){
                if(d == d2){
                    std::vector<std::vector<double>> matrix;
                    matrix.reserve(input_->GetSpaceDimensions());
                    for(int d3 = 0; d3< input_->GetSpaceDimensions(); d3++){
                        matrix.push_back(derivatives[ids[d3]].values_);
                    }
                    fff.push_back(Determinant(matrix));
                }else{
                    fff.push_back(0);
                }
            }

            for(int d2 = 1; d2 < input_->GetSpaceDimensions()+1; d2++){
                std::vector<std::vector<double>> matrix;
                matrix.reserve(input_->GetSpaceDimensions());
                for(int d3 = 0; d3 < input_->GetSpaceDimensions(); d3++){
                    matrix.push_back(derivatives[ids[d2+d3]%input_->GetDimensions()].values_);
                }
                fff.push_back(Determinant(matrix));
            }

            auto vec = new Vector();
            vec->values_ = fff;
            fff_vectors[d].push_back(*vec);
        }
    }

    for(int d = 0; d < input_->GetParameterDimensions(); d++){
        auto feature_flow_field = new VectorField(input_->GetDimensions(),input_->GetSize());
        feature_flow_field->SetData(fff_vectors[d]);
        fffs.push_back(feature_flow_field);
    }
    output_->SetFeatureFlowField(std::move(fffs));
}

double CalculateFFField::Determinant(std::vector<std::vector<double>> matrix) {
    if(matrix.size() == 1){
        return matrix[0][0];
    }else{
        double value = 0;
        for(int i = 0; i < matrix.size(); i++){
            std::vector<std::vector<double>> next_matrix;
            for(int x = 1; x < matrix.size(); x++){
                std::vector<double> next_vector;
                for(int y = 0; y < matrix.size(); y++){
                    if(y != i){
                        next_vector.push_back(matrix[x][y]);
                    }
                }
                next_matrix.push_back(next_vector);
            }
            value += matrix[0][i]*pow(-1,i)*Determinant(next_matrix);
        }
        return value;
    }
}
