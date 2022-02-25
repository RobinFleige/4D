#include <vector>
#include <valarray>
#include "CriticalPointsSet.h"


void CriticalPointsSet::InternalUpdate() {
    output_ = new ProcessObject();
    output_->SetVectorField(input_);
    for(int s = 0; s < input_->GetSize(); s++){
        for(int t = 0; t < input_->GetSize(); t++){
            for(int x = 0; x < input_->GetSize()-1; x++){
                for(int y = 0; y < input_->GetSize()-1; y++){
                    std::vector<std::vector<double>> pixel_set = {input_->GetData(s,t,x,y),input_->GetData(s,t,x+1,y),input_->GetData(s,t,x,y+1),input_->GetData(s,t,x+1,y+1)};
                    //std::cout<<s<<" "<<t<<" "<<x<<" "<<y<<std::endl;
                    if(Subdivide(10,pixel_set)){
                        output_->AppendCriticalPoints({new CriticalPoint({(double)s,(double)t,(double)x,(double)y})});
                    }
                }
            }
        }
    }
}

bool CriticalPointsSet::Subdivide(int max_iterations, std::vector<std::vector<double>> pixel_set) {
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
        for(int i = 0; i < 2; i++){
            mid.push_back((pixel_set[0][i]+pixel_set[1][i]+pixel_set[2][i]+pixel_set[3][i])/4);
        }

        if(max_iterations > 0){
            std::vector<double> top, right, bot, left;
            for(int i = 0; i < 2; i++){
                top.push_back((pixel_set[0][i]+pixel_set[1][i])/2);
                right.push_back((pixel_set[1][i]+pixel_set[3][i])/2);
                bot.push_back((pixel_set[2][i]+pixel_set[3][i])/2);
                left.push_back((pixel_set[0][i]+pixel_set[2][i])/2);
            }
            std::vector<std::vector<std::vector<double>>> sub_pixel_set = {{pixel_set[0],top,left,mid},{top,pixel_set[1],mid,right},{left,mid,pixel_set[2],bot},{mid,right,bot,pixel_set[3]}};
            bool found = false;
            for(int i = 0; i < sub_pixel_set.size(); i++){
                if(Subdivide(max_iterations-1,sub_pixel_set[i])){
                    found = true;
                }
            }
            return found;
        }else{
            return true;
        }
    }else{
        return false;
    }
}

CriticalPointsSet::CriticalPointsSet() {
    Invalidate();
}