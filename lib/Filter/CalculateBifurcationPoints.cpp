#include <vector>
#include <valarray>
#include "CalculateBifurcationPoints.h"


void CalculateBifurcationPoints::InternalUpdate() {
    int size_minus_1 = input_->GetVectorField()->GetSize()-1;
    output_ = input_;
    for(int s = 1; s < size_minus_1; s++){
        for(int t = 1; t < size_minus_1; t++){
            for(int x = 0; x < size_minus_1; x++){
                for(int y = 0; y < size_minus_1; y++){
                    //Dimension{min,max}
                    std::vector<std::vector<double>> min_max_set = {{(double)s,(double)s+1},{(double)t,(double)t+1},{(double)x,(double)x+1},{(double)y,(double)y+1}};
                    //std::cout<<s<<" "<<t<<" "<<x<<" "<<y<<std::endl;
                    output_->AppendCriticalPoints(Subdivide(subdivision_depth_,min_max_set));
                }
            }
        }
    }
}

std::vector<CriticalPoint*> CalculateBifurcationPoints::Subdivide(int max_iterations, std::vector<std::vector<double>> min_max_set) {
    int positive_x = 0;
    int positive_y = 0;
    int positive_fff = 0;
    for(int s = 0; s < 2; s++){
        for(int t = 0; t < 2; t++){
            for(int x = 0; x < 2; x++){
                for(int y = 0; y < 2; y++){
                    if(input_->GetVectorField()->GetInterpolated({min_max_set[0][s],min_max_set[1][t],min_max_set[2][x],min_max_set[3][y]}).values_[0] > 0){
                        positive_x++;
                    }
                    if(input_->GetVectorField()->GetInterpolated({min_max_set[0][s],min_max_set[1][t],min_max_set[2][x],min_max_set[3][y]}).values_[1] > 0){
                        positive_y++;
                    }
                    if(input_->GetVectorField()->GetInterpolatedFFF(min_max_set[0][s],min_max_set[1][t],min_max_set[2][x],min_max_set[3][y],0)[2] > 0){
                        positive_fff++;
                    }
                }
            }
        }
    }

    if(positive_x != 0 && positive_x != 16 && positive_y != 0 && positive_y != 16 && ((positive_fff != 0 && positive_fff != 16) || calculate_critical_points_)){
        if(max_iterations > 0){

            std::vector<std::vector<std::vector<double>>> next_min_max_sets;
            for(int s = 0; s < 2; s++){
                for(int t = 0; t < 2; t++){
                    for(int x = 0; x < 2; x++){
                        for(int y = 0; y < 2; y++){
                            std::vector<std::vector<double>> next_min_max_set;
                            if(s == 0){
                                next_min_max_set.push_back({min_max_set[0][0],(min_max_set[0][0]+min_max_set[0][1])/2});
                            }else{
                                next_min_max_set.push_back({(min_max_set[0][0]+min_max_set[0][1])/2,min_max_set[0][1]});
                            }
                            if(t == 0){
                                next_min_max_set.push_back({min_max_set[1][0],(min_max_set[1][0]+min_max_set[1][1])/2});
                            }else{
                                next_min_max_set.push_back({(min_max_set[1][0]+min_max_set[1][1])/2,min_max_set[1][1]});
                            }
                            if(x == 0){
                                next_min_max_set.push_back({min_max_set[2][0],(min_max_set[2][0]+min_max_set[2][1])/2});
                            }else{
                                next_min_max_set.push_back({(min_max_set[2][0]+min_max_set[2][1])/2,min_max_set[2][1]});
                            }
                            if(y == 0){
                                next_min_max_set.push_back({min_max_set[3][0],(min_max_set[3][0]+min_max_set[3][1])/2});
                            }else{
                                next_min_max_set.push_back({(min_max_set[3][0]+min_max_set[3][1])/2,min_max_set[3][1]});
                            }
                            next_min_max_sets.push_back(next_min_max_set);
                        }
                    }
                }
            }

            std::vector<CriticalPoint*> critical_points;
            for(int i = 0; i < next_min_max_sets.size(); i++){
                std::vector<CriticalPoint*> temp_critical_points;
                temp_critical_points = Subdivide(max_iterations-1,next_min_max_sets[i]);
                for(int j = 0; j < temp_critical_points.size(); j++){
                    critical_points.push_back(temp_critical_points[j]);
                }
            }
            return critical_points;
        }else{
            std::vector<double> mid;
            for(int i = 0; i < 4; i++){
                mid.push_back((min_max_set[i][0]+min_max_set[i][1])/2);
            }
            if(positive_fff != 0 && positive_fff != 16){
                return {new CriticalPoint(mid,CriticalPointType::bifurcation)};
            }else{
                double sum_x;
                double sum_y;
                for(int a = 0; a < 2; a++){
                    sum_x+=input_->GetVectorField()->GetInterpolated({mid[0],mid[1],min_max_set[2][0],min_max_set[3][a]}).values_[0];
                    sum_x-=input_->GetVectorField()->GetInterpolated({mid[0],mid[1],min_max_set[2][1],min_max_set[3][a]}).values_[0];
                    sum_y+=input_->GetVectorField()->GetInterpolated({mid[0],mid[1],min_max_set[2][a],min_max_set[3][0]}).values_[1];
                    sum_y-=input_->GetVectorField()->GetInterpolated({mid[0],mid[1],min_max_set[2][a],min_max_set[3][1]}).values_[1];
                }
                if(sum_x > 0){
                    if(sum_y > 0){
                        return {new CriticalPoint(mid,CriticalPointType::sink)};
                    }else{
                        return {new CriticalPoint(mid,CriticalPointType::saddle)};
                    }
                }else{
                    if(sum_y > 0){
                        return {new CriticalPoint(mid,CriticalPointType::saddle)};
                    }else{
                        return {new CriticalPoint(mid,CriticalPointType::source)};
                    }
                }
            }
        }
    }else{
        return {};
    }
}

CalculateBifurcationPoints::CalculateBifurcationPoints(int subdivision_depth) {
    subdivision_depth_ = subdivision_depth;
    Invalidate();
}

void CalculateBifurcationPoints::SetCalculateCriticalPoints(bool calculate_critical_points) {
    calculate_critical_points_ = calculate_critical_points;
    Invalidate();
}
