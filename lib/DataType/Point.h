#pragma once
#include <vector>


enum CriticalPointType {none =-2, sink = -1, saddle = 0, source = 1, bifurcation = 100};

class Point {
    CriticalPointType type_;
    std::vector<double> coordinates_;

public:
    Point(std::vector<double> coordinates,CriticalPointType type);
    CriticalPointType GetCriticalPointType();
    std::vector<double> GetCoordinates();

};