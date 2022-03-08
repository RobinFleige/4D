#include <vector>
#include <valarray>
#include "CalculateCriticalPoints.h"


void CalculateCriticalPoints::InternalUpdate() {
    output_ = new ProcessObject();
    output_->SetVectorField(input_);
    for(int s = 1; s < input_->GetSize()-1; s++){
        for(int t = 1; t < input_->GetSize()-1; t++){
            for(int x = 0; x < input_->GetSize()-1; x++){
                for(int y = 0; y < input_->GetSize()-1; y++){
                    std::vector<std::vector<double>> ids_set = {{(double)s,(double)t,(double)x,(double)y},{(double)s,(double)t,(double)x+1,(double)y},{(double)s,(double)t,(double)x,(double)y+1},{(double)s,(double)t,(double)x+1,(double)y+1}};
                    //std::cout<<s<<" "<<t<<" "<<x<<" "<<y<<std::endl;
                    output_->AppendCriticalPoints(Subdivide(false,10,ids_set));
                }
            }
        }
    }
}

std::vector<CriticalPoint*> CalculateCriticalPoints::Subdivide(bool interpolate, int max_iterations, std::vector<std::vector<double>> ids_set) {
    std::vector<std::vector<double>> pixel_set;
    for(int i = 0; i < 4; i++){
        if(interpolate){
            pixel_set.push_back(input_->GetInterpolatedSpace(ids_set[i][0], ids_set[i][1], ids_set[i][2], ids_set[i][3]));
        }else{
            pixel_set.push_back(input_->GetData(floor(ids_set[i][0]),floor(ids_set[i][1]),floor(ids_set[i][2]),floor(ids_set[i][3])));
        }
    }
    int positive_x = 0;
    int positive_y = 0;
    for(int i = 0; i < 4; i++){
        if(pixel_set[i][0] > 0){
            positive_x++;
        }
        if(pixel_set[i][1] > 0){
            positive_y++;
        }
    }
    if(positive_x != 4 && positive_x != 0 && positive_y != 4 && positive_y != 0){
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
            return {new CriticalPoint(mid)};
        }
    }else{
        return {};
    }
}

CalculateCriticalPoints::CalculateCriticalPoints() {
    Invalidate();
}