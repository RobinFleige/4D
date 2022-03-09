#include "CalculateFFPoints.h"

CalculateFFPoints::CalculateFFPoints() {
    Invalidate();
}

void CalculateFFPoints::InternalUpdate() {
    std::vector<CriticalPoint*> critical_points = input_->GetCriticalPoints();
    for(int d = 0; d < 2; d++){
        for(int i = 0; i < critical_points.size(); i++){
            //Border Detection
            if(critical_points[i]->GetCoordinates()[0] > 1 && critical_points[i]->GetCoordinates()[1] > 1 && critical_points[i]->GetCoordinates()[2] > 1 && critical_points[i]->GetCoordinates()[3] > 1 && critical_points[i]->GetCoordinates()[0] < input_->GetVectorField()->GetSize()-2 && critical_points[i]->GetCoordinates()[1] < input_->GetVectorField()->GetSize()-2 && critical_points[i]->GetCoordinates()[2] < input_->GetVectorField()->GetSize()-1 && critical_points[i]->GetCoordinates()[3] < input_->GetVectorField()->GetSize()-2){
                //Calculate previous and next values per dimension
                std::vector<double> prev_value_x;
                std::vector<double> next_value_x;
                std::vector<double> prev_value_y;
                std::vector<double> next_value_y;
                std::vector<double> prev_value_p;
                std::vector<double> next_value_p;
                prev_value_x = input_->GetVectorField()->GetInterpolated(critical_points[i]->GetCoordinates()[0],critical_points[i]->GetCoordinates()[1],critical_points[i]->GetCoordinates()[2]-0.5,critical_points[i]->GetCoordinates()[3]);
                next_value_x = input_->GetVectorField()->GetInterpolated(critical_points[i]->GetCoordinates()[0],critical_points[i]->GetCoordinates()[1],critical_points[i]->GetCoordinates()[2]+0.5,critical_points[i]->GetCoordinates()[3]);

                prev_value_y = input_->GetVectorField()->GetInterpolated(critical_points[i]->GetCoordinates()[0],critical_points[i]->GetCoordinates()[1],critical_points[i]->GetCoordinates()[2],critical_points[i]->GetCoordinates()[3]-0.5);
                next_value_y = input_->GetVectorField()->GetInterpolated(critical_points[i]->GetCoordinates()[0],critical_points[i]->GetCoordinates()[1],critical_points[i]->GetCoordinates()[2],critical_points[i]->GetCoordinates()[3]+0.5);

                if(d == 0){
                    prev_value_p = input_->GetVectorField()->GetInterpolated(critical_points[i]->GetCoordinates()[0]-0.5,critical_points[i]->GetCoordinates()[1],critical_points[i]->GetCoordinates()[2],critical_points[i]->GetCoordinates()[3]);
                    next_value_p = input_->GetVectorField()->GetInterpolated(critical_points[i]->GetCoordinates()[0]+0.5,critical_points[i]->GetCoordinates()[1],critical_points[i]->GetCoordinates()[2],critical_points[i]->GetCoordinates()[3]);
                }else{
                    prev_value_p = input_->GetVectorField()->GetInterpolated(critical_points[i]->GetCoordinates()[0],critical_points[i]->GetCoordinates()[1]-0.5,critical_points[i]->GetCoordinates()[2],critical_points[i]->GetCoordinates()[3]);
                    next_value_p = input_->GetVectorField()->GetInterpolated(critical_points[i]->GetCoordinates()[0],critical_points[i]->GetCoordinates()[1]+0.5,critical_points[i]->GetCoordinates()[2],critical_points[i]->GetCoordinates()[3]);
                }

                //Calculate derivatives per dimension
                std::vector<double> derivative_x;
                std::vector<double> derivative_y;
                std::vector<double> derivative_p;
                derivative_x.push_back(next_value_x[0]-prev_value_x[0]);
                derivative_x.push_back(next_value_x[1]-prev_value_x[1]);
                derivative_y.push_back(next_value_y[0]-prev_value_y[0]);
                derivative_y.push_back(next_value_y[1]-prev_value_y[1]);
                derivative_p.push_back(next_value_p[0]-prev_value_p[0]);
                derivative_p.push_back(next_value_p[1]-prev_value_p[1]);

                //Calculate determinants of derivative combinations
                std::vector<double> fff;

                if((derivative_x[0]*derivative_y[1]-derivative_x[1]*derivative_y[0]) < -0.00001){
                    fff.push_back(-(derivative_y[0]*derivative_p[1]-derivative_y[1]*derivative_p[0])/(derivative_x[0]*derivative_y[1]-derivative_x[1]*derivative_y[0]));
                    fff.push_back(-(derivative_p[0]*derivative_x[1]-derivative_p[1]*derivative_x[0])/(derivative_x[0]*derivative_y[1]-derivative_x[1]*derivative_y[0]));
                    fff.push_back(-1);
                }else if((derivative_x[0]*derivative_y[1]-derivative_x[1]*derivative_y[0]) > 0.00001){
                    fff.push_back((derivative_y[0]*derivative_p[1]-derivative_y[1]*derivative_p[0])/(derivative_x[0]*derivative_y[1]-derivative_x[1]*derivative_y[0]));
                    fff.push_back((derivative_p[0]*derivative_x[1]-derivative_p[1]*derivative_x[0])/(derivative_x[0]*derivative_y[1]-derivative_x[1]*derivative_y[0]));
                    fff.push_back(1);
                } else{
                    fff.push_back(1);
                    fff.push_back(1);
                    fff.push_back(0);
                }


                //fff.push_back(derivative_y[0]*derivative_p[1]-derivative_y[1]*derivative_p[0]);
                //fff.push_back(derivative_p[0]*derivative_x[1]-derivative_p[1]*derivative_x[0]);
                //fff.push_back(derivative_x[0]*derivative_y[1]-derivative_x[1]*derivative_y[0]);


                critical_points[i]->AddFFF(fff);
            }else{
                critical_points[i]->AddFFF({0,0,0});
            }
        }
    }
    output_ = input_;
}
