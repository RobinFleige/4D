#include <vector>
#include "CriticalPointsSet.h"


void CriticalPointsSet::InternalUpdate() {
    std::cout<<"CriticalPointSet"<<std::endl;
    for(int i = 0; i < this->input_->GetData().size(); i++){
        std::vector<int> temp_ids = input_->IDsFromID(i);
        bool outer = false;
        for(int j = 0; j < temp_ids.size(); j++){
            if(temp_ids[j] == input_->GetLengths()[j]-1){
                outer = true;
            }
        }
        if(!outer){
            std::vector<double> ids(temp_ids.begin(), temp_ids.end());
            std::vector<std::vector<double>> pixel;
            for(int j = 0; j < pow(2,input_->GetSpaceDimensions()); j++){
                std::vector<double> next_ids;
                for(int k = 0; k < input_->GetSpaceDimensions(); k++){
                    //TODO Calculate the next_ids (Modulo auf pow(2,k) >= pow(2,k-1) -> 1)
                }
                pixel.push_back(input_->GetInterpolated(ids));
            }
            //TODO Adjust Subdivide to work properly
            if(Subdivide(30,pixel)){
                //TODO Insert CriticalPoint
                output_->InsertNextPoint(x,y,0);
            }
        }
    }
}

std::vector<CriticalPoint> CriticalPointsSet::Subdivide(int min_iterations, int max_iterations, std::vector<std::vector<double>> pixel) {
    int positive_x = 0;
    int positive_y = 0;
    for(int i = 0; i < 4; i++){
        if(pixel[i][0] > 0){
            positive_x++;
        }
        if(pixel[i][1] > 0){
            positive_y++;
        }
    }
    if((positive_x != 0 && positive_x != 4 && positive_y != 0 && positive_y != 4)||min_iterations > 0){
        if(max_iterations == 0){
            return true;
        }else{
            double mid[2];
            mid[0] = (pixel[0][0]+pixel[1][0]+pixel[2][0]+pixel[3][0])/4;
            mid[1] = (pixel[0][1]+pixel[1][1]+pixel[2][1]+pixel[3][1])/4;
            double top[2];
            top[0] = (pixel[0][0]+pixel[1][0])/2;
            top[1] = (pixel[0][1]+pixel[1][1])/2;
            double right[2];
            right[0] = (pixel[3][0]+pixel[1][0])/2;
            right[1] = (pixel[3][1]+pixel[1][1])/2;
            double bot[2];
            bot[0] = (pixel[3][0]+pixel[2][0])/2;
            bot[1] = (pixel[3][1]+pixel[2][1])/2;
            double left[2];
            left[0] = (pixel[0][0]+pixel[2][0])/2;
            left[1] = (pixel[0][1]+pixel[2][1])/2;
            std::vector<std::vector<double*>> sub_pixel = {{pixel[0],top,left,mid},{top,pixel[1],mid,right},{left,mid,pixel[2],bot},{mid,right,bot,pixel[3]}};

            bool found = false;
            for(int i = 0; i < 4; i++){
                if(Subdivide(min_iterations-1,max_iterations-1,sub_pixel[i])){
                    found = true;
                }
            }
            return found;
        }
    }
    return false;
}