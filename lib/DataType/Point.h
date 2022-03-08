#pragma once

#include <vector>

class Point {
protected:
    std::vector<double> coordinates_;//per dimension
    std::vector<std::vector<double>> fff_;//per parameter-dimension

public:
    std::vector<double> GetCoordinates();
    Point(std::vector<double> coordinates);
    std::vector<std::vector<double>> GetFFF();
};