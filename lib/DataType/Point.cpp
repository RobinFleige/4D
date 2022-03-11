#include "Point.h"

std::vector<double> Point::GetCoordinates() {
    return coordinates_;
}

Point::Point(std::vector<double> coordinates) {
    coordinates_ = coordinates;
}