#pragma once

class VectorField4D {
private:
    int size_;
    std::vector<std::vector<std::vector<std::vector<std::vector<double>>>>>  values_;
public:
    explicit VectorField4D(int size);
    void SetData(std::vector<std::vector<std::vector<std::vector<std::vector<double>>>>>  values);
    std::vector<std::vector<std::vector<std::vector<std::vector<double>>>>>&  GetData();
    std::vector<std::vector<std::vector<double>>>& GetData(int s, int t);
    std::vector<double>& GetData(int s, int t, int x, int y);
    std::vector<double> GetInterpolatedSpace(double s, double t, double x, double y);
    int GetSize();
    std::vector<double> GetInterpolatedParameter(double s, double t, double x, double y);
};
