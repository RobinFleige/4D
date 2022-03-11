#pragma once

#include <vector>

class Point {
protected:
    std::vector<double> coordinates_;//per dimension

public:
    std::vector<double> GetCoordinates();
    Point(std::vector<double> coordinates);
};