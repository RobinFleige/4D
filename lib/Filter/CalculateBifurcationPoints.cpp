#include <vector>
#include <valarray>
#include "CalculateBifurcationPoints.h"


void CalculateBifurcationPoints::InternalUpdate() {
    output_ = input_;
    for(int i = 0; i < pow(input_->GetVectorField()->GetSize(),input_->GetVectorField()->GetDimensions()); i++){
        std::vector<int> ids = input_->GetVectorField()->IDsFromID(i);
        bool out_of_border = false;
        for(int d = 0; d < input_->GetVectorField()->GetDimensions(); d++){
            if(ids[d] == input_->GetVectorField()->GetSize()-1){
                out_of_border = true;
            }
        }
        if(!out_of_border){
            std::vector<std::vector<double>> min_max_set;
            min_max_set.reserve(input_->GetVectorField()->GetDimensions());
            for(int d = 0; d < input_->GetVectorField()->GetDimensions(); d++){
                min_max_set.push_back({(double)ids[d],(double)ids[d]+1});
            }
            output_->AppendCriticalPoints(Subdivide(param_subdivision_depth_,subdivision_depth_,min_max_set));
        }
    }
}

std::vector<CriticalPoint*> CalculateBifurcationPoints::Subdivide(int max_param_iterations, int max_iterations, std::vector<std::vector<double>> min_max_set) {
    //Setup
    int count = pow(2,input_->GetVectorField()->GetDimensions());
    std::vector<int> positive_counts;
    positive_counts.reserve(input_->GetVectorField()->GetSpaceDimensions()+1);
    for(int i = 0; i < input_->GetVectorField()->GetSpaceDimensions()+1; i++){
        positive_counts.push_back(0);
    }

    //Check for positive and non-positive values for every corner
    for(int i = 0; i < count; i++){
        std::vector<double> ids;
        ids.reserve(input_->GetVectorField()->GetDimensions());
        for(int d = 0; d < input_->GetVectorField()->GetDimensions(); d++){
            if((i%(int)pow(2,d+1))<pow(2,d)){
                ids.push_back(min_max_set[d][0]);
            }else{
                ids.push_back(min_max_set[d][1]);
            }
        }

        for(int d = 0; d < input_->GetVectorField()->GetSpaceDimensions(); d++){
            if(input_->GetVectorField()->GetInterpolated(ids).values_[d] > 0){
                positive_counts[d]+=1;
            }
        }
        if(input_->GetVectorField()->GetInterpolatedFFF(ids,0).values_[0] > 0){
            positive_counts[input_->GetVectorField()->GetSpaceDimensions()]+=1;
        }
    }

    //Calculate if sign change happens
    bool value_change = true;
    bool fff_change = positive_counts[input_->GetVectorField()->GetSpaceDimensions()] != 0 && positive_counts[input_->GetVectorField()->GetSpaceDimensions()] != count;
    for(int d = 0; d < input_->GetVectorField()->GetSpaceDimensions(); d++){
        if(positive_counts[d] == 0 || positive_counts[d] == count){
            value_change = false;
        }
    }

    //If Sign change happened -> Subdivide further
    if(value_change && (fff_change || calculate_critical_points_)){
        if(max_iterations > 0){
            std::vector<std::vector<std::vector<double>>> next_min_max_sets;
            if(max_param_iterations > 0){
                //If Parameter Subdivision
                next_min_max_sets.reserve(count);
                for(int i = 0; i < count; i++){
                    std::vector<std::vector<double>> next_min_max_set;
                    for(int d = 0; d < input_->GetVectorField()->GetDimensions(); d++){
                        if((i%(int)pow(2,d+1))<pow(2,d)){
                            next_min_max_set.push_back({min_max_set[d][0],(min_max_set[d][0]+min_max_set[d][1])/2});
                        }else{
                            next_min_max_set.push_back({(min_max_set[d][0]+min_max_set[d][1])/2,min_max_set[d][1]});
                        }
                    }
                    next_min_max_sets.push_back(next_min_max_set);
                }
            }else{
                int temp_count = (int)pow(2,input_->GetVectorField()->GetSpaceDimensions());
                //If Not Parameter Subdivision
                next_min_max_sets.reserve(temp_count);
                for(int i = 0; i < temp_count; i++){
                    std::vector<std::vector<double>> next_min_max_set;
                    for(int d = 0; d < input_->GetVectorField()->GetParameterDimensions(); d++){
                        next_min_max_set.push_back({min_max_set[d][0],min_max_set[d][1]});
                    }
                    for(int d = 0; d < input_->GetVectorField()->GetSpaceDimensions(); d++){
                        if((i%(int)pow(2,d+1))<pow(2,d)){
                            next_min_max_set.push_back({min_max_set[d+input_->GetVectorField()->GetParameterDimensions()][0],(min_max_set[d+input_->GetVectorField()->GetParameterDimensions()][0]+min_max_set[d+input_->GetVectorField()->GetParameterDimensions()][1])/2});
                        }else{
                            next_min_max_set.push_back({(min_max_set[d+input_->GetVectorField()->GetParameterDimensions()][0]+min_max_set[d+input_->GetVectorField()->GetParameterDimensions()][1])/2,min_max_set[d+input_->GetVectorField()->GetParameterDimensions()][1]});
                        }
                    }
                    next_min_max_sets.push_back(next_min_max_set);
                }
            }

            //Call Subdivision and return their returns
            std::vector<CriticalPoint*> critical_points;
            for(int i = 0; i < next_min_max_sets.size(); i++){
                std::vector<CriticalPoint*> temp_critical_points;
                temp_critical_points = Subdivide(max_param_iterations-1,max_iterations-1,next_min_max_sets[i]);
                for(int j = 0; j < temp_critical_points.size(); j++){
                    critical_points.push_back(temp_critical_points[j]);
                }
            }
            return critical_points;
        }else{
            //Create new CriticalPoint
            //Calculate Coordinates
            std::vector<double> mid;
            for(int i = 0; i < input_->GetVectorField()->GetDimensions(); i++){
                mid.push_back((min_max_set[i][0]+min_max_set[i][1])/2);
            }
            //If FFF Changed it is a Bifurcation
            if(fff_change){
                return {new CriticalPoint(mid,CriticalPointType::bifurcation)};
            }else{
                //Else check for Vector Direction
                std::vector<double> dimension_sum;
                dimension_sum.reserve(input_->GetVectorField()->GetSpaceDimensions());
                for(int d = 0; d < input_->GetVectorField()->GetSpaceDimensions(); d++){
                    dimension_sum.push_back(0);
                    for(int d2 = 0; d2 < pow(2,input_->GetVectorField()->GetSpaceDimensions()); d2++){
                        std::vector<double> ids;
                        bool plus;
                        for(int d3 = 0; d3 < input_->GetVectorField()->GetParameterDimensions(); d3++){
                            ids.push_back(mid[d3]);
                        }
                        for(int d3 = 0; d3 < input_->GetVectorField()->GetSpaceDimensions(); d3++){
                            if((d2%(int)pow(2,d3+1))<pow(2,d3)){
                                ids.push_back(min_max_set[d3+input_->GetVectorField()->GetParameterDimensions()][0]);
                                if(d3 == d){
                                    plus = true;
                                }
                            }else{
                                ids.push_back(min_max_set[d3+input_->GetVectorField()->GetParameterDimensions()][1]);
                                if(d3 == d){
                                    plus = false;
                                }
                            }
                        }

                        if(plus){
                            dimension_sum[d]+=input_->GetVectorField()->GetInterpolated(ids).values_[d];
                        }else{
                            dimension_sum[d]-=input_->GetVectorField()->GetInterpolated(ids).values_[d];
                        }
                    }

                }

                //Calculate in how many Dimensions the neighbouring vector shows towards the coordinates
                int positive_dimensions = 0;
                for(int i = 0; i < input_->GetVectorField()->GetSpaceDimensions(); i++){
                    if(dimension_sum[i] > 0){
                        positive_dimensions++;
                    }
                }

                //If all dimensions show towards, it is a sink; If al dimensions show away it is a source; Else it is a saddle
                if(positive_dimensions == 0){
                    return {new CriticalPoint(mid,CriticalPointType::sink)};
                }else if(positive_dimensions == input_->GetVectorField()->GetSpaceDimensions()){
                    return {new CriticalPoint(mid,CriticalPointType::source)};
                }else{
                    return {new CriticalPoint(mid,CriticalPointType::saddle)};
                }
            }
        }
    }else{
        return {};
    }
}

CalculateBifurcationPoints::CalculateBifurcationPoints(int param_subdivision_depth, int subdivision_depth) {
    name_ = "CalculateBifurcationPoints";
    param_subdivision_depth_ = param_subdivision_depth;
    subdivision_depth_ = subdivision_depth;
    Invalidate();
}

void CalculateBifurcationPoints::SetCalculateCriticalPoints(bool calculate_critical_points) {
    calculate_critical_points_ = calculate_critical_points;
    Invalidate();
}