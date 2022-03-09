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
                    std::vector<std::vector<double>> ids_set = {{(double)s,(double)t,(double)x,(double)y},{(double)s,(double)t,(double)x+1,(double)y},{(double)s,(double)t,(double)x,(double)y+1},{(double)s,(double)t,(double)x+1,(double)y+1}};
                    std::cout<<s<<" "<<t<<" "<<x<<" "<<y<<std::endl;
                    output_->AppendCriticalPoints(Subdivide(false,2,ids_set));
                }
            }
        }
    }
}

std::vector<CriticalPoint*> CalculateBifurcationPoints::Subdivide(bool interpolate, int max_iterations, std::vector<std::vector<double>> ids_set) {
    std::vector<std::vector<double>> pixel_set;
    std::vector<double> fff3_set;
    for(int i = 0; i < 4; i++){
        if(interpolate){
            pixel_set.push_back(input_->GetVectorField()->GetData(ids_set[i][0],ids_set[i][1])->GetInterpolated(ids_set[i][2], ids_set[i][3]));
            fff3_set.push_back(input_->GetVectorField()->GetInterpolatedFFF3(ids_set[i][0],ids_set[i][1],ids_set[i][2], ids_set[i][3]));
        }else{
            pixel_set.push_back(input_->GetVectorField()->GetData(floor(ids_set[i][0]),floor(ids_set[i][1]),floor(ids_set[i][2]),floor(ids_set[i][3])));
            fff3_set.push_back(input_->GetVectorField()->GetFFF3(ids_set[i][0],ids_set[i][1],ids_set[i][2], ids_set[i][3]));
        }
    }
    //Ich muss durch alle 4 Dimensionen gehen, also 16, nicht 4 Sätze im ids_set
    int positive_x = 0;
    int positive_y = 0;
    int positive_fff = 0;
    for(int i = 0; i < 4; i++){
        if(pixel_set[i][0] > 0){
            positive_x++;
        }
        if(pixel_set[i][1] > 0){
            positive_y++;
        }
        if(fff3_set[i] > 0){
            positive_fff++;
        }
    }

    if(positive_x != 0 && positive_x != 4 && positive_y != 0 && positive_y != 4 && positive_fff != 0 && positive_fff != 4){
        std::vector<double> mid;
        for(int i = 0; i < 4; i++){
            mid.push_back((ids_set[0][i]+ids_set[1][i]+ids_set[2][i]+ids_set[3][i])/4);
        }

        if(max_iterations > 0){
            std::vector<double> top, right, bot, left;
            for(int i = 0; i < 4; i++){
                top.push_back((ids_set[0][i]+ids_set[1][i])/2);
                right.push_back((ids_set[1][i]+ids_set[3][i])/2);
                bot.push_back((ids_set[2][i]+ids_set[3][i])/2);
                left.push_back((ids_set[0][i]+ids_set[2][i])/2);
            }
            std::vector<std::vector<std::vector<double>>> sub_ids_set = {{ids_set[0],top,left,mid},{top,ids_set[1],mid,right},{left,mid,ids_set[2],bot},{mid,right,bot,ids_set[3]}};
            std::vector<CriticalPoint*> critical_points;
            for(int i = 0; i < sub_ids_set.size(); i++){
                std::vector<CriticalPoint*> temp_critical_points;
                temp_critical_points = Subdivide(true,max_iterations-1,sub_ids_set[i]);
                for(int j = 0; j < temp_critical_points.size(); j++){
                    critical_points.push_back(temp_critical_points[j]);
                }
            }
            return critical_points;
        }else{
            std::cout<<mid[0]<<" "<<mid[1]<<" "<<mid[2]<<" "<<mid[3]<<std::endl;
            return {new CriticalPoint(mid,CriticalPointType::bifurcation)};
        }
    }else{
        return {};
    }
}

CalculateBifurcationPoints::CalculateBifurcationPoints() {
    Invalidate();
}