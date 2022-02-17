#include <vector>
#include <valarray>
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
            std::vector<std::vector<double>> ids_set;
            for(int j = 0; j < pow(2,input_->GetSpaceDimensions()); j++){
                std::vector<double> next_ids;
                for(int k = 0; k < input_->GetParameterDimensions(); k++){
                    next_ids.push_back(ids[k]);
                }
                for(int k = 0; k < input_->GetSpaceDimensions(); k++){
                    double next_id = ids[k+input_->GetParameterDimensions()];
                    //TODO Calculate the next_ids (Modulo auf pow(2,k) >= pow(2,k-1) -> 1)
                    if(j%((int)pow(2,k+1)) >= pow(2,k)){
                        next_id = next_id+1;
                    }
                    next_ids.push_back(next_id);
                }
                ids_set.push_back(next_ids);
            }
            output_->AppendCriticalPoints(Subdivide(1,5,ids_set));
        }
    }
}

std::vector<CriticalPoint*> CriticalPointsSet::Subdivide(int min_iterations, int max_iterations, std::vector<std::vector<double>> ids_set) {

    bool change = false;
    if(min_iterations > 0){
        change = true;
    }else{
        std::vector<int> positive_per_dimension;
        for(int j = 0; j < input_->GetSpaceDimensions(); j++){
            positive_per_dimension.push_back(0);
        }
        for(int i = 0; i < ids_set.size(); i++){
            for(int j = 0; j < input_->GetSpaceDimensions(); j++){
                if(input_->GetInterpolated(ids_set[i])[j+input_->GetParameterDimensions()] > 0){
                    positive_per_dimension[j]++;
                }
            }
        }
        for(int i = 0; i < input_->GetSpaceDimensions(); i++){
            if(positive_per_dimension[i] != 0 && positive_per_dimension[i] != ids_set.size()){
                change = true;
            }
        }
    }


    if(change){//TODO Calculate for higher dimensions
        std::vector<double> mid;
        mid.push_back((ids_set[0][0]+ids_set[1][0]+ids_set[2][0]+ids_set[3][0])/4);
        mid.push_back((ids_set[0][1]+ids_set[1][1]+ids_set[2][1]+ids_set[3][1])/4);
        mid.push_back((ids_set[0][2]+ids_set[1][2]+ids_set[2][2]+ids_set[3][2])/4);
        mid.push_back((ids_set[0][3]+ids_set[1][3]+ids_set[2][3]+ids_set[3][3])/4);
        if(max_iterations == 0){
            return {new CriticalPoint(mid)};
        }else{
            std::vector<double> top;
            top.push_back((ids_set[0][0]+ids_set[1][0])/2);
            top.push_back((ids_set[0][1]+ids_set[1][1])/2);
            top.push_back((ids_set[0][2]+ids_set[1][2])/2);
            top.push_back((ids_set[0][3]+ids_set[1][3])/2);
            std::vector<double> right;
            right.push_back((ids_set[3][0]+ids_set[1][0])/2);
            right.push_back((ids_set[3][1]+ids_set[1][1])/2);
            right.push_back((ids_set[3][2]+ids_set[1][2])/2);
            right.push_back((ids_set[3][3]+ids_set[1][3])/2);
            std::vector<double> bot;
            bot.push_back((ids_set[3][0]+ids_set[2][0])/2);
            bot.push_back((ids_set[3][1]+ids_set[2][1])/2);
            bot.push_back((ids_set[3][2]+ids_set[2][2])/2);
            bot.push_back((ids_set[3][3]+ids_set[2][3])/2);
            std::vector<double> left;
            left.push_back((ids_set[0][0]+ids_set[2][0])/2);
            left.push_back((ids_set[0][1]+ids_set[2][1])/2);
            left.push_back((ids_set[0][2]+ids_set[2][2])/2);
            left.push_back((ids_set[0][3]+ids_set[2][3])/2);
            std::vector<std::vector<std::vector<double>>> sub_pixel = {{ids_set[0],top,left,mid},{top,ids_set[1],mid,right},{left,mid,ids_set[2],bot},{mid,right,bot,ids_set[3]}};


            std::vector<CriticalPoint*> points;
            for(int i = 0; i < sub_pixel.size(); i++){
                std::vector<CriticalPoint*> temp_points = Subdivide(min_iterations-1,max_iterations-1,sub_pixel[i]);
                for(int j = 0; j < temp_points.size(); j++){
                    points.push_back(temp_points[j]);
                }
            }
            return points;
        }
    }
    return {};
}