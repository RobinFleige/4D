#pragma once

class VectorField2D {
private:
    int size_;
    std::vector<std::vector<std::vector<double>>> values_;
public:
    explicit VectorField2D(int size);
    void SetData(std::vector<std::vector<std::vector<double>>> values);
    std::vector<std::vector<std::vector<double>>>& GetData();
    std::vector<double>& GetData(int x, int y);
    int GetSize();
};