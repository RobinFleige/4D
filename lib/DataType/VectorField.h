#pragma once

class VectorField {
private:
    int size_;
    std::vector<std::vector<std::vector<double>>> values_;
public:
    explicit VectorField(int size);
    void SetData(std::vector<std::vector<std::vector<double>>> values);
    std::vector<std::vector<std::vector<double>>>& GetData();
    std::vector<double>& GetData(int x, int y);
    std::vector<double> GetInterpolated(double x, double y);
    int GetSize();
};