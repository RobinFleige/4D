#include "CalculateFFField.h"

CalculateFFField::CalculateFFField() {
    Invalidate();
}

void CalculateFFField::InternalUpdate() {
    output_ = input_;
    int size = input_->GetVectorField()->GetSize();
    std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<double>>>>>> feature_flow_field;
    feature_flow_field.reserve(size);
    for(int s = 0; s < size; s++){
        std::vector<std::vector<std::vector<std::vector<std::vector<double>>>>> txyd_vector;
        txyd_vector.reserve(size);
        for(int t = 0; t < size; t++){
            std::vector<std::vector<std::vector<std::vector<double>>>> xyd_vector;
            xyd_vector.reserve(size);
            for(int x = 0; x < size; x++){
                std::vector<std::vector<std::vector<double>>> yd_vector;
                yd_vector.reserve(size);
                for(int y = 0; y < size; y++){
                    std::vector<std::vector<double>>d_vector;
                    d_vector.reserve(2);
                    for(int d = 0; d < 2; d++){
                        //Calculate previous and next values per dimension
                        double x_factor = 1;
                        double y_factor = 1;
                        double p_factor = 1;
                        Vector prev_value_x;
                        Vector next_value_x;
                        Vector prev_value_y;
                        Vector next_value_y;
                        Vector prev_value_p;
                        Vector next_value_p;

                        if(x > 0){
                            prev_value_x = input_->GetVectorField()->GetInterpolated({(double)s,(double)t,x-0.5,(double)y});
                        }else{
                            prev_value_x = input_->GetVectorField()->GetInterpolated({(double)s,(double)t,0,(double)y});
                            x_factor=2;
                        }
                        if(x < input_->GetVectorField()->GetSize()-1){
                            next_value_x = input_->GetVectorField()->GetInterpolated({(double)s,(double)t,x+0.5,(double)y});
                        }else{
                            next_value_x = input_->GetVectorField()->GetInterpolated({(double)s,(double)t,(double)input_->GetVectorField()->GetSize()-1,(double)y});
                            x_factor=2;
                        }
                        if(y > 0){
                            prev_value_y = input_->GetVectorField()->GetInterpolated({(double)s,(double)t,(double)x,y-0.5});
                        }else{
                            prev_value_y = input_->GetVectorField()->GetInterpolated({(double)s,(double)t,(double)x,0});
                            y_factor=2;
                        }
                        if(y < input_->GetVectorField()->GetSize()-1){
                            next_value_y = input_->GetVectorField()->GetInterpolated({(double)s,(double)t,(double)x,y+0.5});
                        }else{
                            next_value_y = input_->GetVectorField()->GetInterpolated({(double)s,(double)t,(double)x,(double)input_->GetVectorField()->GetSize()-1});
                            y_factor=2;
                        }

                        if(d == 0){
                            if(s > 0){
                                prev_value_p = input_->GetVectorField()->GetInterpolated({s-0.5,(double)t,(double)x,(double)y});
                            }else{
                                prev_value_p = input_->GetVectorField()->GetInterpolated({0,(double)t,(double)x,(double)y});
                                p_factor=2;
                            }
                            if(s < input_->GetVectorField()->GetSize()-1){
                                next_value_p = input_->GetVectorField()->GetInterpolated({s+0.5,(double)t,(double)x,(double)y});
                            }else{
                                next_value_p = input_->GetVectorField()->GetInterpolated({(double)input_->GetVectorField()->GetSize()-1,(double)t,(double)x,(double)y});
                                p_factor=2;
                            }
                        }else{
                            if(t > 0){
                                prev_value_p = input_->GetVectorField()->GetInterpolated({(double)s,t-0.5,(double)x,(double)y});
                            }else{
                                prev_value_p = input_->GetVectorField()->GetInterpolated({(double)s,0,(double)x,(double)y});
                                p_factor=2;
                            }
                            if(t < input_->GetVectorField()->GetSize()-1){
                                next_value_p = input_->GetVectorField()->GetInterpolated({(double)s,t+0.5,(double)x,(double)y});
                            }else{
                                next_value_p = input_->GetVectorField()->GetInterpolated({(double)s,(double)input_->GetVectorField()->GetSize()-1,(double)x,(double)y});
                                p_factor=2;
                            }
                        }

                        //Calculate derivatives per dimension
                        std::vector<double> derivative_x;
                        std::vector<double> derivative_y;
                        std::vector<double> derivative_p;
                        derivative_x.push_back((next_value_x.values_[0]-prev_value_x.values_[0])*x_factor);
                        derivative_x.push_back((next_value_x.values_[1]-prev_value_x.values_[1])*x_factor);
                        derivative_y.push_back((next_value_y.values_[0]-prev_value_y.values_[0])*y_factor);
                        derivative_y.push_back((next_value_y.values_[1]-prev_value_y.values_[1])*y_factor);
                        derivative_p.push_back((next_value_p.values_[0]-prev_value_p.values_[0])*p_factor);
                        derivative_p.push_back((next_value_p.values_[1]-prev_value_p.values_[1])*p_factor);

                        //Calculate determinants of derivative combinations
                        std::vector<double> fff;
                        fff.push_back(derivative_y[0]*derivative_p[1]-derivative_y[1]*derivative_p[0]);
                        fff.push_back(derivative_p[0]*derivative_x[1]-derivative_p[1]*derivative_x[0]);
                        fff.push_back(derivative_x[0]*derivative_y[1]-derivative_x[1]*derivative_y[0]);
                        d_vector.push_back(fff);
                    }
                    yd_vector.push_back(d_vector);
                }
                xyd_vector.push_back(yd_vector);
            }
            txyd_vector.push_back(xyd_vector);
        }
        feature_flow_field.push_back(txyd_vector);
    }
    output_->GetVectorField()->SetFeatureFlowField(std::move(feature_flow_field));
}
