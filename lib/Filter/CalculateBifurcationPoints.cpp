#include <vector>
#include <valarray>
#include "CalculateBifurcationPoints.h"


void CalculateBifurcationPoints::InternalUpdate() {
    output_ = input_;
    for(int i = 0; i < pow(input_->GetSize(),input_->GetDimensions()); i++){

        if(i%1000==0){
            std::cout<<i<<std::endl;
        }

        std::vector<int> ids = input_->IDsFromID(i);
        if(!OnRightBorder(ids)){
            std::vector<std::vector<double>> min_max_set = CalculateMinMaxSet(ids);
            output_->AppendCriticalPoints(Subdivide(param_subdivision_depth_,subdivision_depth_,min_max_set));
        }
    }
}

std::vector<Point*> CalculateBifurcationPoints::Subdivide(int max_param_iterations, int max_iterations, std::vector<std::vector<double>> min_max_set) {
    //Setup
    int count = (int)pow(2,input_->GetDimensions());
    int space_count = (int)pow(2,input_->GetSpaceDimensions());
    std::vector<int> positive_counts;

    //Check for positive and non-positive values for every corner
    std::vector<std::vector<double>> min_max_corners = CalculateMinMaxCorners(min_max_set);
    positive_counts = CalculatePositiveCounts(min_max_corners);

    //Calculate if sign change happens
    bool value_change = true;
    for(int d = 0; d < input_->GetSpaceDimensions(); d++){
        if(positive_counts[d] == 0 || positive_counts[d] == space_count){
            value_change = false;
        }
    }
    bool fff_change = positive_counts[input_->GetSpaceDimensions()] != 0 && positive_counts[input_->GetSpaceDimensions()] != space_count;

    //If Sign change happened -> Subdivide further
    if(value_change && (fff_change || calculate_critical_points_)){
        if(max_iterations > 0){
            std::vector<std::vector<std::vector<double>>> next_min_max_sets = CalculateNextMinMaxSets(min_max_set, max_param_iterations > 0);

            //Call Subdivision and return their returns
            std::vector<Point*> critical_points;
            for(int i = 0; i < next_min_max_sets.size(); i++){
                std::vector<Point*> temp_critical_points;
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
            for(int i = 0; i < input_->GetDimensions(); i++){
                mid.push_back((min_max_set[i][0]+min_max_set[i][1])/2);
            }
            //If FFF Changed it is a Bifurcation
            if(fff_change){
                return {new Point(mid,CriticalPointType::bifurcation)};
            }else{
                //std::cout<<input_->GetInterpolatedFFF(mid,0).values_[0]<<" "<<input_->GetInterpolatedFFF(mid,0).values_[1]<<" "<<input_->GetInterpolatedFFF(mid,0).values_[2]<<" "<<input_->GetInterpolatedFFF(mid,0).values_[3]<<" "<<std::endl;
                //std::cout<<mid[0]<<" "<<mid[1]<<" "<<mid[2]<<" "<<mid[3]<<" "<<std::endl;
                //Else check for Vector Direction
                int positive_dimensions = CalculateDimensionDirection(mid, min_max_set);

                //If all dimensions show towards, it is a sink; If al dimensions show away it is a source; Else it is a saddle
                if(positive_dimensions == 0){
                    return {new Point(mid,CriticalPointType::sink)};
                }else if(positive_dimensions == input_->GetSpaceDimensions()){
                    return {new Point(mid,CriticalPointType::source)};
                }else{
                    return {new Point(mid,CriticalPointType::saddle)};
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

bool CalculateBifurcationPoints::OnRightBorder(std::vector<int> ids) {
    bool out_of_border = false;
    for(int d = 0; d < input_->GetDimensions(); d++){
        if(ids[d] == input_->GetSize()-1){
            out_of_border = true;
        }
    }
    return out_of_border;
}

std::vector<std::vector<double>> CalculateBifurcationPoints::CalculateMinMaxSet(std::vector<int> ids) {
    std::vector<std::vector<double>> min_max_set;
    min_max_set.reserve(input_->GetDimensions());
    for(int d = 0; d < input_->GetDimensions(); d++){
        min_max_set.push_back({(double)ids[d],(double)ids[d]+1});
    }
    return min_max_set;
}

std::vector<std::vector<double>> CalculateBifurcationPoints::CalculateMinMaxCorners(std::vector<std::vector<double>> min_max_set) {
    std::vector<std::vector<double>> min_max_corners;
    for(int i = 0; i < (int)pow(2,input_->GetSpaceDimensions()); i++){
        std::vector<double> ids;
        ids.reserve(input_->GetDimensions());
        for(int d = 0; d < input_->GetParameterDimensions(); d++){
            ids.push_back((min_max_set[d][0]+min_max_set[d][1])/2);
        }
        for(int d = 0; d < input_->GetSpaceDimensions(); d++){
            if((i%(int)pow(2,d+1))<pow(2,d)){
                ids.push_back(min_max_set[d+input_->GetParameterDimensions()][0]);
            }else{
                ids.push_back(min_max_set[d+input_->GetParameterDimensions()][1]);
            }
        }
        min_max_corners.push_back(ids);
    }
    return min_max_corners;
}

std::vector<int> CalculateBifurcationPoints::CalculatePositiveCounts(std::vector<std::vector<double>> min_max_corners) {
    std::vector<int> positive_counts;
    int positive_type_count = input_->GetSpaceDimensions()+1;
    positive_counts.reserve(positive_type_count);
    for(int i = 0; i < positive_type_count; i++){
        positive_counts.push_back(0);
    }
    for(int i = 0; i < (int)pow(2,input_->GetSpaceDimensions()); i++){
        for(int d = 0; d < input_->GetSpaceDimensions(); d++){
            if(input_->GetInterpolated(min_max_corners[i]).values_[d] > 0){
                positive_counts[d]+=1;
            }
        }
        if(input_->GetInterpolatedFFF(min_max_corners[i],0).values_[0] > 0){
            positive_counts[input_->GetSpaceDimensions()]+=1;
        }
    }
    return positive_counts;
}

std::vector<std::vector<std::vector<double>>> CalculateBifurcationPoints::CalculateNextMinMaxSets(std::vector<std::vector<double>> min_max_set, bool subdivide_parameters) {
    std::vector<std::vector<std::vector<double>>> next_min_max_sets;
    int count = pow(2,input_->GetDimensions());

    if(subdivide_parameters > 0){
        //If Parameter Subdivision
        next_min_max_sets.reserve(count);
        for(int i = 0; i < count; i++){
            std::vector<std::vector<double>> next_min_max_set;
            next_min_max_set.reserve(input_->GetDimensions());
            for(int d = 0; d < input_->GetDimensions(); d++){
                if((i%(int)pow(2,d+1))<pow(2,d)){
                    next_min_max_set.push_back({min_max_set[d][0],(min_max_set[d][0]+min_max_set[d][1])/2});
                }else{
                    next_min_max_set.push_back({(min_max_set[d][0]+min_max_set[d][1])/2,min_max_set[d][1]});
                }
            }
            next_min_max_sets.push_back(next_min_max_set);
        }
    }else{
        int temp_count = (int)pow(2,input_->GetSpaceDimensions());
        //If Not Parameter Subdivision
        next_min_max_sets.reserve(temp_count);
        for(int i = 0; i < temp_count; i++){
            std::vector<std::vector<double>> next_min_max_set;
            next_min_max_set.reserve(input_->GetDimensions());
            for(int d = 0; d < input_->GetParameterDimensions(); d++){
                next_min_max_set.push_back({min_max_set[d][0],min_max_set[d][1]});
            }
            for(int d = 0; d < input_->GetSpaceDimensions(); d++){
                if((i%(int)pow(2,d+1))<pow(2,d)){
                    next_min_max_set.push_back({min_max_set[d+input_->GetParameterDimensions()][0],(min_max_set[d+input_->GetParameterDimensions()][0]+min_max_set[d+input_->GetParameterDimensions()][1])/2});
                }else{
                    next_min_max_set.push_back({(min_max_set[d+input_->GetParameterDimensions()][0]+min_max_set[d+input_->GetParameterDimensions()][1])/2,min_max_set[d+input_->GetParameterDimensions()][1]});
                }
            }
            next_min_max_sets.push_back(next_min_max_set);
        }
    }
    return next_min_max_sets;
}

int CalculateBifurcationPoints::CalculateDimensionDirection(std::vector<double> mid, std::vector<std::vector<double>> min_max_set) {
    std::vector<double> dimension_sum;
    dimension_sum.reserve(input_->GetSpaceDimensions());


    for(int d = 0; d < input_->GetSpaceDimensions(); d++){
        dimension_sum.push_back(0);

        for(int i = 0; i < input_->GetSpaceDimensions(); i++){
            std::vector<double> ids1;
            std::vector<double> ids2;
            for(int d2 = 0; d2 < input_->GetParameterDimensions(); d2++){
                ids1.push_back(mid[d2]);
                ids2.push_back(mid[d2]);
            }

            for(int d2 = 0; d2 < input_->GetSpaceDimensions(); d2++){
                if(i == d2){
                    ids1.push_back(min_max_set[d2+input_->GetParameterDimensions()][0]);
                    ids2.push_back(min_max_set[d2+input_->GetParameterDimensions()][1]);
                }else{
                    ids1.push_back(mid[d2+input_->GetParameterDimensions()]);
                    ids2.push_back(mid[d2+input_->GetParameterDimensions()]);
                }
            }
            dimension_sum[d]+=input_->GetInterpolated(ids1).values_[d];
            dimension_sum[d]-=input_->GetInterpolated(ids2).values_[d];
        }
    }

    //Calculate in how many Dimensions the neighbouring vector shows towards the coordinates
    int positive_dimensions = 0;
    for(int i = 0; i < input_->GetSpaceDimensions(); i++){
        if(dimension_sum[i] > 0){
            positive_dimensions++;
        }
    }
    return positive_dimensions;
}
