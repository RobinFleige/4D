#pragma once

class VectorField4D {
private:
    int size_;
    std::vector<std::vector<std::vector<std::vector<std::vector<double>>>>> values_;
public:
    VectorField4D(int size);
    void SetData(std::vector<std::vector<std::vector<std::vector<std::vector<double>>>>> values);
    std::vector<std::vector<std::vector<std::vector<std::vector<double>>>>> GetData();
    int GetSize();
};