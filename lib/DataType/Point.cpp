#include "Point.h"

Point::Point(std::vector<double> coordinates, CriticalPointType type){
    coordinates_ = coordinates;
    type_ = type;
}

CriticalPointType Point::GetCriticalPointType() {
    return type_;
}

std::vector<double> Point::GetCoordinates() {
    return coordinates_;
}

